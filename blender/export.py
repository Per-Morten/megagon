import os
import bpy
import bmesh

# input
scale   = 1

# @doc https://blender.stackexchange.com/questions/45698/triangulate-mesh-in-python - 21.04.2018
def triangulate(obj):
    me = obj.data
    # Get a BMesh representation
    bm = bmesh.new()
    bm.from_mesh(me)

    bmesh.ops.triangulate(bm, faces=bm.faces[:], quad_method=0, ngon_method=0)

    # Finish up, write the bmesh back to the mesh
    bm.to_mesh(me)
    bm.free()


def writeVertices(outfile, vertices):
    global scale
    outfile.write("vertices: {}\n".format(len(vertices)))
    for vc in vertices:
        outfile.write("v: {:9.6f} {:9.6f} {:9.6f}\n".format( 
                vc.co[0]*scale,
                vc.co[1]*scale,
                vc.co[2]*scale))
                


def writeTriangles(outfile, polygons):
    
    outfile.write("triangles: {}\n".format(len(polygons)))
    for p in polygons:
        if len(p.vertices) != 3:
            print("ERROR, TRIANGULATE YOUR MESH!!!!")
            exit(-1)
            
        outfile.write("t: {} {} {}\n".format(
            p.vertices[0],
            p.vertices[1],
            p.vertices[2]
        ))

if __name__ == "__main__":

    active_object = bpy.context.active_object
    
    mesh = active_object.data

    vertices = mesh.vertices
    polygons = mesh.polygons

    # If not triangulated!
    if len(polygons[0].vertices) != 3:
        triangulate(active_object)
   
    # @debug info 
    print("Active name:", active_object.name)
    print("Vertexcount: ", len(vertices))
    print("TriangleCount: ", len(polygons))      
    print("Outputfile:", "output/"+active_object.name+".yml")
    outfile = open("output/"+active_object.name+".yml", "w")
    
    writeVertices(outfile, vertices)
    outfile.write("\n")

    writeTriangles(outfile, polygons)
        
    outfile.close()

