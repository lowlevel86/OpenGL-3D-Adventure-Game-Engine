#!BPY

"""
Name: 'C code tex (.c)...'
Blender: 249
Group: 'Export'
Tip: 'Export to C code with texture.'
"""

import Blender
from Blender import Window
import math

#write the vertice xyz coordinates to file
#first the quads then the trigons for each mesh
def writeVertices(file, ob):
	global meshCnt
	file.write("//quad array %i\n" % (meshCnt))
	mesh = ob.getData()
	i = 0
	for face in mesh.faces:
		if len(mesh.faces[i]) == 4:
			file.write("%f, %f, %f,\n" % (mesh.verts[mesh.faces[i][0].index][0],
							         mesh.verts[mesh.faces[i][0].index][1],
							         mesh.verts[mesh.faces[i][0].index][2]))
			file.write("%f, %f, %f,\n" % (mesh.verts[mesh.faces[i][1].index][0],
							         mesh.verts[mesh.faces[i][1].index][1],
							         mesh.verts[mesh.faces[i][1].index][2]))
			file.write("%f, %f, %f,\n" % (mesh.verts[mesh.faces[i][2].index][0],
							         mesh.verts[mesh.faces[i][2].index][1],
							         mesh.verts[mesh.faces[i][2].index][2]))
			file.write("%f, %f, %f,\n" % (mesh.verts[mesh.faces[i][3].index][0],
							         mesh.verts[mesh.faces[i][3].index][1],
							         mesh.verts[mesh.faces[i][3].index][2]))
		i += 1
	file.write("//trigon array %i\n" % (meshCnt))
	mesh = ob.getData()
	i = 0
	for face in mesh.faces:
		if len(mesh.faces[i]) == 3:
			file.write("%f, %f, %f,\n" % (mesh.verts[mesh.faces[i][0].index][0],
							         mesh.verts[mesh.faces[i][0].index][1],
							         mesh.verts[mesh.faces[i][0].index][2]))
			file.write("%f, %f, %f,\n" % (mesh.verts[mesh.faces[i][1].index][0],
							         mesh.verts[mesh.faces[i][1].index][1],
							         mesh.verts[mesh.faces[i][1].index][2]))
			file.write("%f, %f, %f,\n" % (mesh.verts[mesh.faces[i][2].index][0],
							         mesh.verts[mesh.faces[i][2].index][1],
							         mesh.verts[mesh.faces[i][2].index][2]))
		i += 1


#write the quad data to file
#first the quads and make room for the trigons
def WriteQuadFaces(file, ob):
	global meshCnt
	global meshPointDataCnt
	file.write("//data array %i\n" % (meshCnt))
	mesh = ob.getData()
	i = 0
	for face in mesh.faces:
		face_v = face.v
		if len(face_v) == 4:
			file.write("%i, " % (i + 0 + meshPointDataCnt))
			file.write("%i, " % (i + 1 + meshPointDataCnt))
			file.write("%i, " % (i + 2 + meshPointDataCnt))
			file.write("%i,\n" % (i + 3 + meshPointDataCnt))
			i += 4
	for face in mesh.faces:
		face_v = face.v
		if len(face_v) == 3:
			i += 3
	meshPointDataCnt += i

#write the trigon data to file
#skipping the quad data sequences
def WriteTriFaces(file, ob):
	global meshCnt
	global meshPointDataCnt
	file.write("//data array %i\n" % (meshCnt))
	mesh = ob.getData()
	i = 0
	for face in mesh.faces:
		face_v = face.v
		if len(face_v) == 4:
			i += 4
	for face in mesh.faces:
		face_v = face.v
		if len(face_v) == 3:
			file.write("%i, " % (i + 0 + meshPointDataCnt))
			file.write("%i, " % (i + 1 + meshPointDataCnt))
			file.write("%i,\n" % (i + 2 + meshPointDataCnt))
			i += 3
	meshPointDataCnt += i


#write the vertex color data to file
#first quads then trigons
def WriteColors(file, ob):
	global meshCnt
	file.write("//quad array %i\n" % (meshCnt))
	mesh = ob.getData()
	for i, f in enumerate(mesh.faces):
		if len(f.col): # if vertex color exists
			if len(f) == 4:
				for n, v in enumerate(f):
					file.write("%i, %i, %i, %i,\n" % (f.col[n].r, f.col[n].g, f.col[n].b, 0x7F))
		else:
			if len(f) == 4:
				for n, v in enumerate(f):
					file.write("%i, %i, %i, %i,\n" % (0xFF, 0xFF, 0xFF, 0x7F))
	file.write("//trigon array %i\n" % (meshCnt))
	mesh = ob.getData()
	for i, f in enumerate(mesh.faces):
		if len(f.col): # if vertex color exists
			if len(f) == 3:
				for n, v in enumerate(f):
					file.write("%i, %i, %i, %i,\n" % (f.col[n].r, f.col[n].g, f.col[n].b, 0x7F))
		else:
			if len(f) == 3:
				for n, v in enumerate(f):
					file.write("%i, %i, %i, %i,\n" % (0xFF, 0xFF, 0xFF, 0x7F))


#write the texture coordinates data to file
#first quads then trigons
def WriteTexCoords(file, ob):
	global meshCnt
	file.write("//quad array %i\n" % (meshCnt))
	mesh = ob.getData()
	i = 0
	for face in mesh.faces:
		if mesh.faces[i].uv:
			if len(face.v) == 4:
				file.write("%f, %f,\n" % (mesh.faces[i].uv[0][0],
							  mesh.faces[i].uv[0][1]))
				file.write("%f, %f,\n" % (mesh.faces[i].uv[1][0],
							  mesh.faces[i].uv[1][1]))
				file.write("%f, %f,\n" % (mesh.faces[i].uv[2][0],
							  mesh.faces[i].uv[2][1]))
				file.write("%f, %f,\n" % (mesh.faces[i].uv[3][0],
							  mesh.faces[i].uv[3][1]))
		else:
			if len(face.v) == 4:
				file.write("%f, %f,\n" % (0.0, 0.0))
				file.write("%f, %f,\n" % (1.0, 0.0))
				file.write("%f, %f,\n" % (1.0, 1.0))
				file.write("%f, %f,\n" % (0.0, 1.0))
		i += 1
	file.write("//trigon array %i\n" % (meshCnt))
	mesh = ob.getData()
	i = 0
	for face in mesh.faces:
		if mesh.faces[i].uv:
			if len(face.v) == 3:
				file.write("%f, %f,\n" % (mesh.faces[i].uv[0][0],
							  mesh.faces[i].uv[0][1]))
				file.write("%f, %f,\n" % (mesh.faces[i].uv[1][0],
							  mesh.faces[i].uv[1][1]))
				file.write("%f, %f,\n" % (mesh.faces[i].uv[2][0],
							  mesh.faces[i].uv[2][1]))
		else:
			if len(face.v) == 3:
				file.write("%f, %f,\n" % (0.0, 0.0))
				file.write("%f, %f,\n" % (1.0, 0.0))
				file.write("%f, %f,\n" % (1.0, 1.0))
		i += 1


# script main function
def ExportToC(file_name):
	file = open(file_name, "w")
	
	scene = Blender.Scene.GetCurrent()
	meshes = []
	for ob in scene.objects:
		obtype = ob.type
		if obtype == "Mesh":
			meshes.append(ob)
	
	#Sort meshes alphabetically
	meshNames = []
	sortedMeshNames = []
	for mesh in meshes:
		meshNames.append(mesh.getName())
		sortedMeshNames.append(mesh.getName())
	
	sortedMeshNames.sort()
	
	sortedMeshes = []
	for sortedMeshName in sortedMeshNames:
		sortedMeshes.append(meshes[meshNames.index(sortedMeshName)])
	meshes = sortedMeshes


	global meshCnt
	global meshPointDataCnt
	
	#change to object mode
	in_editmode = Window.EditMode()
	if in_editmode: Window.EditMode(0)


	contentName = Blender.sys.splitext(Blender.sys.basename(file_name))[0]
	
	#Print the transformation data to file
	meshCnt = 0
	file.write("//transformation data\n")
	file.write("//x, y, z, rotation\n")
	file.write("//x, y, z, location\n")
	file.write("//x, y, z, size\n")
	file.write("//y, z, unit circle coordinates for x rotation\n")
	file.write("//x, z, unit circle coordinates for y rotation\n")
	file.write("//x, y, unit circle coordinates for z rotation\n")
	file.write("//bounds radius,\n")
	file.write("float %s_TRANS[%i]={\n" % (contentName, len(meshes) * 16))
	for mesh in meshes:
		file.write("//data block %i\n" % (meshCnt))
		file.write("%f, %f, %f,\n" % (mesh.rot[0]*180.0/math.pi,
                                              mesh.rot[1]*180.0/math.pi,
                                              mesh.rot[2]*180.0/math.pi))
		file.write("%f, %f, %f,\n" % (mesh.loc[0], mesh.loc[1], mesh.loc[2]))
		file.write("%f, %f, %f,\n" % (mesh.size[0], mesh.size[1], mesh.size[2]))

		file.write("%f, %f,\n" % (math.cos(mesh.rot[0]),
					  math.sin(mesh.rot[0])))
		file.write("%f, %f,\n" % (math.cos(mesh.rot[1]),
					  math.sin(mesh.rot[1])))
		file.write("%f, %f,\n" % (math.cos(mesh.rot[2]),
					  math.sin(mesh.rot[2])))
		xyLgth = math.sqrt(mesh.size[0]*mesh.size[0]+mesh.size[1]*mesh.size[1])
		file.write("%f,\n" % (math.sqrt(xyLgth*xyLgth+mesh.size[2]*mesh.size[2])))
		meshCnt += 1
	file.write("};\n\n")
	
	#Get the number of corners of each polygon
	polyCornerCnt = 0
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 3:
				polyCornerCnt += 3
			elif len(face.v) == 4:
				polyCornerCnt += 4


	#Count the number of quads
	quadCount = 0
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 4:
				quadCount += 1

	#Count the number of trigon
	trigonCount = 0
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 3:
				trigonCount += 1

	#Print the point data to file
	file.write("//point data\n")
	file.write("float %s_POINT[%i]={\n" % (contentName, polyCornerCnt * 3))
	meshCnt = 0
	for mesh in meshes:
		writeVertices(file, mesh)
		meshCnt += 1
	file.write("};\n\n")
	

	#Print the quad data to file
	meshCnt = 0
	meshPointDataCnt = 0
	file.write("//quad data\n")
	file.write("short %s_QUAD[%i]={\n" % (contentName, quadCount * 4))
	for mesh in meshes:
		WriteQuadFaces(file, mesh)
		meshCnt += 1
	file.write("};\n\n")
	
	#Print the trigon data to file
	meshCnt = 0
	meshPointDataCnt = 0
	file.write("//trigon data\n")
	file.write("short %s_TRI[%i]={\n" % (contentName, trigonCount * 3))
	for mesh in meshes:
		WriteTriFaces(file, mesh)
		meshCnt += 1
	file.write("};\n\n")
	
	#Print the vertex color data to file
	file.write("//vertex color data\n")
	file.write("char %s_VCOLOR[%i]={\n" % (contentName, quadCount*4*4 + trigonCount*3*4))
	meshCnt = 0
	for mesh in meshes:
		WriteColors(file, mesh)
		meshCnt += 1
	file.write("};\n\n")
	
	#Print the texture coordinate data to file
	file.write("//texture coordinate data\n")
	file.write("float %s_TEXCOORD[%i]={\n" % (contentName, quadCount*4*2 + trigonCount*3*2))
	meshCnt = 0
	for mesh in meshes:
		WriteTexCoords(file, mesh)
		meshCnt += 1
	file.write("};\n\n")

	#Get the textures and the object to texture links
	imgUsedBuff = []
	texBuff = []
	imgFilename = []
	for mesh in meshes:
		if mesh.getData().faces:
			if mesh.getData().faces[0].image:
				imgUsed = False
				imgNum = 0
				for img in imgUsedBuff:
					imgFilename = mesh.getData().faces[0].image.getFilename().split("/")
					imgFilename = imgFilename[len(imgFilename)-1].split("\\")
					if imgFilename[len(imgFilename)-1] == img:
						imgUsed = True
						break
					imgNum += 1
				texBuff.append(imgNum)
				if imgUsed == False:
					imgFilename = mesh.getData().faces[0].image.getFilename().split("/")
					imgFilename = imgFilename[len(imgFilename)-1].split("\\")
					imgUsedBuff.append(imgFilename[len(imgFilename)-1])
			else:
				texBuff.append(-1)

		else:
			texBuff.append(-1)

	#Print object to texture links
	i = 0
	file.write("//texture link number for each object\n")
	file.write("int %s_TEXLINKDAT[%i]={\n" % (contentName, len(meshes)))
	for tex in texBuff:
     		file.write("%i,\n" % (tex))
		i += 1
	file.write("};\n\n")
	
	#Print the number of textures
	file.write("//number of textures\n")
	file.write("int %s_TEXCNT = %i;\n\n" % (contentName, len(imgUsedBuff)))

	
	#Print the point data array sizes to file
	polyCornerCnt = 0
	file.write("//point data array sizes\n")
	file.write("int %s_POINTDATSZ[%i]={\n" % (contentName, len(meshes)+1))
	file.write("0,\n")
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 3:
				polyCornerCnt += 3
			elif len(face.v) == 4:
				polyCornerCnt += 4
		file.write("%i,\n" % (polyCornerCnt * 3))
	file.write("};\n\n")
	
	#Print the quad data array sizes to file
	polyCornerCnt = 0
	file.write("//quad data array sizes\n")
	file.write("int %s_QUADDATSZ[%i]={\n" % (contentName, len(meshes)+1))
	file.write("0,\n")
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 4:
				polyCornerCnt += 4
		file.write("%i,\n" % (polyCornerCnt))
	file.write("};\n\n")
	
	#Print the trigon data array sizes to file
	polyCornerCnt = 0
	file.write("//trigon data array sizes\n")
	file.write("int %s_TRIDATSZ[%i]={\n" % (contentName, len(meshes)+1))
	file.write("0,\n")
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 3:
				polyCornerCnt += 3
		file.write("%i,\n" % (polyCornerCnt))
	file.write("};\n\n")
	
	#Print the vertex color data array sizes to file
	polyCornerCnt = 0
	file.write("//vertex color data array sizes\n")
	file.write("int %s_VCOLORDATSZ[%i]={\n" % (contentName, len(meshes)+1))
	file.write("0,\n")
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 3:
				polyCornerCnt += 3
			elif len(face.v) == 4:
				polyCornerCnt += 4
		file.write("%i,\n" % (polyCornerCnt * 4))
	file.write("};\n\n")
	
	#Print the texture coordinate data array sizes to file
	polyCornerCnt = 0
	file.write("//texture coordinate data array sizes\n")
	file.write("int %s_TEXCOORDDATSZ[%i]={\n" % (contentName, len(meshes)+1))
	file.write("0,\n")
	for mesh in meshes:
		for face in mesh.getData().faces:
			if len(face.v) == 3:
				polyCornerCnt += 3
			elif len(face.v) == 4:
				polyCornerCnt += 4
		file.write("%i,\n" % (polyCornerCnt * 2))
	file.write("};\n\n")
	
	#Print visibility statis
	file.write("//visibility 0 = False 1 = True\n")
	file.write("int %s_HIDE[%i]={\n" % (contentName, len(meshes)))
	for mesh in meshes:
		file.write("%i,\n" % (0))
	file.write("};\n\n")

	#Print the number of meshes
	file.write("//number of meshes\n")
	file.write("int %s_MESHCNT = %i;\n" % (contentName, len(meshes)))
	
	file.close()
	
	
	#Write the header file
	headerName = Blender.sys.dirname(file_name)
	headerName += '/'
	headerName += Blender.sys.splitext(Blender.sys.basename(file_name))[0]
	headerName += '.h'
	file = open(headerName, "w")
	
	file.write("extern float %s_TRANS[%i];\n" % (contentName, len(meshes) * 16))
	file.write("extern float %s_POINT[%i];\n" % (contentName, quadCount*4*3 + trigonCount*3*3))
	file.write("extern short %s_QUAD[%i];\n" % (contentName, quadCount*4))
	file.write("extern short %s_TRI[%i];\n" % (contentName, trigonCount*3))
	file.write("extern char %s_VCOLOR[%i];\n" % (contentName, quadCount*4*4 + trigonCount*3*4))
	file.write("extern float %s_TEXCOORD[%i];\n\n" % (contentName, quadCount*4*2 + trigonCount*3*2))

	file.write("extern int %s_TEXLINKDAT[%i];\n" % (contentName, len(meshes)))
	file.write("extern int %s_TEXCNT;\n" % (contentName))
	file.write("int %s_TEX[%i];\n\n" % (contentName, len(imgUsedBuff)))

	file.write("extern int %s_POINTDATSZ[%i];\n" % (contentName, len(meshes)+1))
	file.write("extern int %s_QUADDATSZ[%i];\n" % (contentName, len(meshes)+1))
	file.write("extern int %s_TRIDATSZ[%i];\n" % (contentName, len(meshes)+1))
	file.write("extern int %s_VCOLORDATSZ[%i];\n" % (contentName, len(meshes)+1))
	file.write("extern int %s_TEXCOORDDATSZ[%i];\n\n" % (contentName, len(meshes)+1))

	file.write("extern int %s_HIDE[%i];\n\n" % (contentName, len(meshes)))

	file.write("//unchanging transformation data\n")
	file.write("float %s_STATICTRANS[%i];\n\n" % (contentName, len(meshes) * 16))

	file.write("//unchanging point data\n")
	file.write("float %s_STATICPOINT[%i];\n\n" % (contentName, quadCount*4*3 + trigonCount*3*3))

	file.write("extern int %s_MESHCNT;\n\n" % (contentName))
	
	#Print the names of the objects
	i = 0
	file.write("//mesh names\n")
	for mesh in meshes:
     		file.write("#define %s_" % (contentName))
		for objNameChar in mesh.getName():
			if objNameChar != ".":
     				file.write("%c" % (objNameChar))
			else:
     				file.write("%c" % ("_"))
     		file.write(" %i\n" % (i))
		i += 1
     	file.write("\n")

	#Print texture names
	i = 0
	file.write("//textures\n")
	for img in imgUsedBuff:
     		file.write("#define %s_" % (contentName))
		for imgChar in img:
			if imgChar != ".":
	     			file.write("%s" % (imgChar))
			else:
	     			file.write("%s" % ("_"))
     		file.write(" %i\n" % (i))
		i += 1


	file.close()
	
	
def FileSelectorCB(file_name):
	if not file_name.lower().endswith('.c'):
		file_name += '.c'
	ExportToC(file_name)

if __name__ == '__main__':
	Blender.Window.FileSelector(FileSelectorCB, "Export to C (tex)", Blender.sys.makename(ext='.c'))
