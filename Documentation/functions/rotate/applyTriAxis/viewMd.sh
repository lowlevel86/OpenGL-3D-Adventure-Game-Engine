#!/bin/bash
pandoc -s --toc applyRotLocSz.md -o applyRotLocSz.html
xlinks2 applyRotLocSz.html
