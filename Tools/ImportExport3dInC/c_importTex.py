#!BPY

"""
Name: 'C code tex (.c)...'
Blender: 249
Group: 'Import'
Tip: 'Import from C code with texture.'
"""

import bpy
import Blender
import math
from Blender import Mesh,Object,Material,Texture,Image,Draw

# script main function
def ImportFromC(file_name):
	print ("\n" * 2)
	print ("_" * 20)
	print ("\n" * 2)
	print "Beginning import from c script..."
	print ("\n" * 2)

	#get header filename from filename
	print file_name
	stringParts = file_name.split(".")
	
	headerFile_name = ""
	for i in range(0, len(stringParts)-1):
		headerFile_name += stringParts[i]
		headerFile_name += "."

	headerFile_name += "h"

	#open and read header file
	file = open(headerFile_name, "r")

	code = [l_split for l in file.readlines() for l_split in (' '.join(l.split()),) if l_split]
	fileLinePos = 0
	fileColPos = 0

	cDefineNames = []
	cDefineValues = []
	cDefineCount = 0

	print "Finding c defines"
	while True:
		# find the listed c defines
		fileLineCount = len(code)
		doesExist = False
		for i in range(0, fileLineCount-fileLinePos): #for (i=0; i < sizeof(code); i++)
			if code[fileLinePos+i][0:len("#define")] == "#define":
				fileLinePos += i
				cDefineCount += 1
				doesExist = True
				break

		# break the while loop if c defines are not found
		if doesExist == False:
			break

		# find the first underscore
		fileColCount = len(code[fileLinePos])
		for i in range(0, fileColCount): #for (i=0; i < sizeof(code[fileLinePos]); i++)
			if code[fileLinePos][i] == "_":
				fileColPos = i+1
				break
	
		# read c define name after the first underscore
		cDefName = ''
		for i in range(0, fileColCount-fileColPos):
			if code[fileLinePos][fileColPos+i] == " ":
				fileColPos += i+1
				break
			cDefName += code[fileLinePos][fileColPos+i]
		cDefineNames.append(cDefName)

		# read c define value
		cDefVal = ''
		for i in range(0, fileColCount-fileColPos):
			cDefVal += code[fileLinePos][fileColPos+i]
		cDefineValues.append(int(cDefVal))

		fileLinePos += 1

	objectNames = []
	imageNamesUnderscore = []
	imageNames = []

	# seperate the c defines into object and image names

	# find where the image Names are located within c defines
	imagesLoc = cDefineCount
	for i in range(1, cDefineCount):
		if cDefineValues[i] == 0:
			imagesLoc = i
			break

	# get the object names
	for i in range(0, imagesLoc):
		objectNames.append(cDefineNames[i])
	
	# get the image names
	for i in range(imagesLoc, cDefineCount):
		imgNameUnder = []
		for j in range(0, len(cDefineNames[i])):
			imgNameUnder.append(cDefineNames[i][j])
		imageNamesUnderscore.extend([imgNameUnder])

	# find the last underscore in each of the image names
	# and change it to a period
	for i in range(0, len(imageNamesUnderscore)):
		for j in range(0, len(imageNamesUnderscore[i])):
			if imageNamesUnderscore[i][len(imageNamesUnderscore[i])-j-1] == "_":
				imageNamesUnderscore[i][len(imageNamesUnderscore[i])-j-1] = "."
				break

	for i in range(0, len(imageNamesUnderscore)):
		imgName = ''
		for j in range(0, len(imageNamesUnderscore[i])):
			imgName += imageNamesUnderscore[i][j]
		imageNames.append(imgName)
	
	#close header file
	file.close()

	#open and read c file
	file = open(file_name, "r")

	scene = bpy.data.scenes.active
	meshes = []
	for ob in scene.objects:
		obtype = ob.type
		if obtype == "Mesh":
			meshes.append(ob)

	fileLines = [l_split for l in file.readlines() for l_split in (' '.join(l.split()),) if l_split]

	print "Erasing all comments"
	# erase all of the comments (/* */)
	i = 0
	insideComment = 0
	while i < len(fileLines):
		stopErase = 0
		
		commentStart = fileLines[i].find("/*")
		if insideComment == 1:
			commentStart = 0
			
		if fileLines[i].find("//") != -1:
			if fileLines[i].find("//") < commentStart:
				stopErase = 1
		if stopErase != 1:
			if commentStart != -1:
				insideComment = 1
	
		lineEnd = len(fileLines[i])
		commentEnd = fileLines[i].find("*/")
		
		if commentEnd != -1:
			if insideComment == 1:
				commentEnd = fileLines[i].find("*/")+2
				insideComment = 0
		else:
			if insideComment == 1:
				commentEnd = lineEnd
		
		if commentStart != -1:
			if fileLines[i].find("//") != -1:
				if fileLines[i].find("//") < commentStart:
					stopErase = 1
				if fileLines[i].find("//")+2 < commentEnd:
					stopErase = 1
			if stopErase != 1:
				fileLines[i] = fileLines[i].replace(fileLines[i][commentStart:commentEnd], "")
		
		commentStart = fileLines[i].find("/*")
		if commentStart == -1:
			i = i + 1
		if stopErase == 1:
			i = i + 1

	# erase all of the comments (//)
	i = 0
	while i < len(fileLines):
		commentStart = fileLines[i].find("//")
		commentEnd = len(fileLines[i])
		if commentStart != -1:
			fileLines[i] = fileLines[i].replace(fileLines[i][commentStart:commentEnd], "")
		i = i + 1
	
	print "Erasing all spaces"
	# erase all spaces
	i = 0
	while i < len(fileLines):
		fileLines[i] = fileLines[i].replace(" ", "")
		i = i + 1
	
	print "Moving code to buffer"
	# move the data from "fileLines" buffer to "code" buffer ignoring returns
	i = 0
	code = []
	while i < len(fileLines):
		lineEnd = len(fileLines[i])
		j = 0
		while j < lineEnd:
			code[len(code):] = fileLines[i][j]
			j = j + 1
		i = i + 1
	
##################################################################################################

	codePos = 0

	print "Finding vertex array size"
	# find the first listed vertex array size
	i = 0
	while i < len(code):
		if code[0+i:12+i] == ["_", "P", "O", "I", "N", "T", "D", "A", "T", "S", "Z", "["]:
			codePos = i + 12
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1

	print "Reading vertex array sizes"
	# read the vertex array sizes from the code
	endOfNum = 0
	numCnt = 0
	pointDatSz = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i

		if num != "":
			pointDatSz[len(pointDatSz):] = [int(num)]
	print pointDatSz
	#number of meshes
	meshCnt = len(pointDatSz)-1
	
	print "Finding quad array size"
	# find the first listed quad array size
	i = 0
	while i < len(code):
		if code[0+i:11+i] == ["_", "Q", "U", "A", "D", "D", "A", "T", "S", "Z", "["]:
			codePos = i + 11
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1

	print "Reading quad array sizes"
	# read the quad array sizes from the code
	endOfNum = 0
	numCnt = 0
	quadDatSz = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		
		if num != "":
			quadDatSz[len(quadDatSz):] = [int(num)]
	

	print "Finding tri array size"
	# find the first listed tri array size
	i = 0
	while i < len(code):
		if code[0+i:10+i] == ["_", "T", "R", "I", "D", "A", "T", "S", "Z", "["]:
			codePos = i + 10
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1

	print "Reading tri array sizes"
	# read the tri array sizes from the code
	endOfNum = 0
	numCnt = 0
	triDatSz = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i

		if num != "":
			triDatSz[len(triDatSz):] = [int(num)]
	
	
##################################################################################################

	print "Finding fist listed vertex"
	# find the first listed vertex
	i = 0
	while i < len(code):
		if code[0+i:7+i] == ["_", "P", "O", "I", "N", "T", "["]:
			codePos = i + 7
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1
	
	print "Reading verticies"
	# read the verticies from the code
	endOfNum = 0
	vert = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		
		if num != "":
			vert[len(vert):] = [float(num)]
	

	print "Finding first listed quad"
	# find the first listed quad data number
	i = 0
	while i < len(code):
		if code[0+i:6+i] == ["_", "Q", "U", "A", "D", "["]:
			codePos = i + 6
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1
	
	print "Reading quads"
	# read the quad data from the code
	endOfNum = 0
	quad = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		
		if num != "":
			quad[len(quad):] = [int(num)]



	print "Finding first listed tri"
	# find the first listed tri data number
	i = 0
	while i < len(code):
		if code[0+i:5+i] == ["_", "T", "R", "I", "["]:
			codePos = i + 5
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1
	
	print "Reading tris"
	# read the tri data from the code
	endOfNum = 0
	tri = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		
		if num != "":
			tri[len(tri):] = [int(num)]


	print "Finding first listed vertex color"
	# find the first listed vertex color data number
	i = 0
	while i < len(code):
		if code[0+i:8+i] == ["_", "V", "C", "O", "L", "O", "R", "["]:
			codePos = i + 8
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1
	
	print "Reading vertex color"
	# read the vertex color data from the code
	endOfNum = 0
	vColor = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		
		if num != "":
			vColor[len(vColor):] = [int(num)]


	print "Finding first listed texture coordinate"
	# find the first listed texture coordinate data number
	i = 0
	while i < len(code):
		if code[0+i:8+i] == ["_", "T", "E", "X", "C", "O", "O", "R", "D", "["]:
			codePos = i + 8
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1
	
	print "Reading texture coordinates"
	# read the texture coordinate data from the code
	endOfNum = 0
	texCoord = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		
		if num != "":
			texCoord[len(texCoord):] = [float(num)]


	print "Finding first listed texture link data"
	# find the first listed texture link data number
	i = 0
	while i < len(code):
		if code[0+i:8+i] == ["_", "T", "E", "X", "L", "I", "N", "K", "D", "A", "T", "["]:
			codePos = i + 8
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1
	
	print "Reading texture link data"
	# read the texture link data from the code
	endOfNum = 0
	texLinkDat = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		if num != "":
			texLinkDat[len(texLinkDat):] = [int(num)]

##################################################################################################

	vColorInc = 0
	texCoordInc = 0
	for meshInc in range(0, meshCnt):
		print ("meshInc %i" % (meshInc))
		mesh = Mesh.New()
		
		print "Importing verticies"
		# import verticies to blender
		i = pointDatSz[meshInc]
		while i < pointDatSz[meshInc+1]:
			mesh.verts.extend(vert[i],vert[i+1],vert[i+2])
			i = i + 3

		print "Importing quads"
		# import quads to blender
		i = quadDatSz[meshInc]
		polyBgn = pointDatSz[meshInc] / 3
		while i < quadDatSz[meshInc+1]:
			mesh.faces.extend(quad[i]-polyBgn, quad[i+1]-polyBgn, quad[i+2]-polyBgn, quad[i+3]-polyBgn)
			i = i + 4
		
		print "Importing tris"
		# import tris to blender
		i = triDatSz[meshInc]
		polyBgn = pointDatSz[meshInc] / 3
		while i < triDatSz[meshInc+1]:
			mesh.faces.extend(tri[i]-polyBgn, tri[i+1]-polyBgn, tri[i+2]-polyBgn)
			i = i + 3
		

		# enable vertex colors
		mesh.vertexColors = 1

		print "Importing vertex colors"
		# import vertex colors for quads to blender

		faceCnt = 0

		i = quadDatSz[meshInc]
		while i < quadDatSz[meshInc+1]:

			mesh.faces[faceCnt].col[0].r = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[0].g = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[0].b = vColor[vColorInc]
			vColorInc += 2

			mesh.faces[faceCnt].col[1].r = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[1].g = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[1].b = vColor[vColorInc]
			vColorInc += 2

			mesh.faces[faceCnt].col[2].r = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[2].g = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[2].b = vColor[vColorInc]
			vColorInc += 2

			mesh.faces[faceCnt].col[3].r = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[3].g = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[3].b = vColor[vColorInc]
			vColorInc += 2

			faceCnt += 1
			i += 4

		# import vertex colors for tris to blender
		i = triDatSz[meshInc]
		while i < triDatSz[meshInc+1]:

			mesh.faces[faceCnt].col[0].r = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[0].g = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[0].b = vColor[vColorInc]
			vColorInc += 2

			mesh.faces[faceCnt].col[1].r = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[1].g = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[1].b = vColor[vColorInc]
			vColorInc += 2

			mesh.faces[faceCnt].col[2].r = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[2].g = vColor[vColorInc]
			vColorInc += 1
			mesh.faces[faceCnt].col[2].b = vColor[vColorInc]
			vColorInc += 2

			faceCnt += 1
			i += 3


		# if object has texture than make "faceUV" true
		if texLinkDat[meshInc] != -1:
			mesh.faceUV = True
		else:
			mesh.faceUV = False

		print "Importing texture coordinates"
		# import texture coordinate for quads to blender

		uvFaceCnt = 0

		i = quadDatSz[meshInc]
		if texLinkDat[meshInc] != -1:
			while i < quadDatSz[meshInc+1]:

				mesh.faces[uvFaceCnt].uv[0].x = texCoord[texCoordInc]
				texCoordInc += 1
				mesh.faces[uvFaceCnt].uv[0].y = texCoord[texCoordInc]
				texCoordInc += 1

				mesh.faces[uvFaceCnt].uv[1].x = texCoord[texCoordInc]
				texCoordInc += 1
				mesh.faces[uvFaceCnt].uv[1].y = texCoord[texCoordInc]
				texCoordInc += 1

				mesh.faces[uvFaceCnt].uv[2].x = texCoord[texCoordInc]
				texCoordInc += 1
				mesh.faces[uvFaceCnt].uv[2].y = texCoord[texCoordInc]
				texCoordInc += 1

				mesh.faces[uvFaceCnt].uv[3].x = texCoord[texCoordInc]
				texCoordInc += 1
				mesh.faces[uvFaceCnt].uv[3].y = texCoord[texCoordInc]
				texCoordInc += 1

				uvFaceCnt += 1
				i += 4
		else:
			texCoordInc += (quadDatSz[meshInc+1]-i)/4*8
			uvFaceCnt += (quadDatSz[meshInc+1]-i)/4

		# import texture coordinate for tris to blender
		i = triDatSz[meshInc]
		if texLinkDat[meshInc] != -1:
			while i < triDatSz[meshInc+1]:

				mesh.faces[uvFaceCnt].uv[0].x = texCoord[texCoordInc]
				texCoordInc += 1
				mesh.faces[uvFaceCnt].uv[0].y = texCoord[texCoordInc]
				texCoordInc += 1

				mesh.faces[uvFaceCnt].uv[1].x = texCoord[texCoordInc]
				texCoordInc += 1
				mesh.faces[uvFaceCnt].uv[1].y = texCoord[texCoordInc]
				texCoordInc += 1

				mesh.faces[uvFaceCnt].uv[2].x = texCoord[texCoordInc]
				texCoordInc += 1
				mesh.faces[uvFaceCnt].uv[2].y = texCoord[texCoordInc]
				texCoordInc += 1

				uvFaceCnt += 1
				i += 3
		else:
			texCoordInc += (triDatSz[meshInc+1]-i)/3*6
			uvFaceCnt += (triDatSz[meshInc+1]-i)/3

		# import image files to blender
		print "Importing texture data"
		tex_dir = Blender.sys.dirname(file_name) + "/texture/"
		
		for i in range(0, len(imageNames)):
			try:
				imgData = Image.Load(Blender.sys.join(tex_dir, imageNames[i]))
			except IOError:
				continue
			else:
				if texLinkDat[meshInc] == i:
					for f in mesh.faces:
						f.image = imgData
		
		scene.objects.new(mesh)
	
##################################################################################################

	scene = Blender.Scene.GetCurrent()
	meshes = []
	i = len(objectNames)-1
	for ob in scene.objects:
		obtype = ob.type
		if obtype == "Mesh":
			meshes.append(ob)

		# rename objects
		if i >= 0:
			ob.name = objectNames[i]
			i -= 1


	print "Importing trasformation data for each mesh object"

	# find the first listed transformation data value
	i = 0
	while i < len(code):
		if code[0+i:7+i] == ["_", "T", "R", "A", "N", "S", "["]:
			codePos = i + 7
			i = len(code)
		i = i + 1
	
	i = codePos
	while i < len(code):
		if code[0+i:3+i] == ["]", "=", "{"]:
			codePos = i + 3
			i = len(code)
		i = i + 1

	# read the transformation data from the code
	endOfNum = 0
	numCnt = 0
	trans = []
	while endOfNum != 2:
		i = 0
		num = ""
		endOfNum = 0
		while endOfNum == 0:
			if code[codePos+i] == "," or code[codePos+i] == "}":
				endOfNum = 1
			else:
				num = num + code[codePos+i]
			if code[codePos+i] == "}":
				endOfNum = 2
			i = i + 1
		
		if endOfNum != 2:
			codePos = codePos+i
		
		if num != "":
			trans[len(trans):] = [float(num)]
	
	#Read the transformation data from file
	i = 0
	matrix = ob.getMatrix()
	while i < meshCnt:
		meshes[meshCnt-1-i].rot = [trans[i*16+0]*math.pi/180.0, trans[i*16+1]*math.pi/180.0, trans[i*16+2]*math.pi/180.0]
		meshes[meshCnt-1-i].loc = [trans[i*16+3], trans[i*16+4], trans[i*16+5]]
		meshes[meshCnt-1-i].size = [trans[i*16+6], trans[i*16+7], trans[i*16+8]]
		i = i + 1
	
	#close c file
	file.close()

def my_callback(filename):
	ImportFromC(filename)

if __name__ == '__main__':
	Blender.Window.FileSelector(my_callback, "Import C code (tex)", "*.c")
