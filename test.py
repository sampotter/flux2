import sys; sys.path.insert(0, './build/lib.linux-x86_64-3.8')

import embree
import flux
import numpy as np

shape_model = '67p-xlarge'
obj_path = shape_model + '.obj'
verts_path = shape_model + '-verts.npy'
faces_path = shape_model + '-faces.npy'

verts = np.load(verts_path)
faces = np.load(faces_path)
shape_model = flux.ShapeModel(verts, faces)

e = lambda n, i: np.eye(n)[i].astype(np.float32)

N = 2**16
bsize = 2**8

shape_model.mul_with_ff(0, N, 0, N, np.ones(N), bsize)
