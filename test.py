import sys; sys.path.insert(0, './build/lib.macosx-10.15-x86_64-3.7')

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

shape_model.mul_with_ff(0, 1024, 0, 1024, e(1024, 1), 128)
