#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

glm::vec3 computeFaceNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a, b, n;
    double l;
    
    a.x = p2.x - p1.x;
    a.y = p2.y - p1.y;
    a.z = p2.z - p1.z;

    b.x = p3.x - p1.x;
    b.y = p3.y - p1.y;
    b.z = p3.z - p1.z;

    n.x = (a.y * b.z) - (a.z * b.y);
    n.y = (a.z * b.x) - (a.x * b.z);
    n.z = (a.x * b.y) - (a.y * b.x);

    l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
    n.x /= l;
    n.y /= l;
    n.z /= l;

    return n;
}

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec3> & out_normals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		} else if ( strcmp( lineHeader, "f" ) == 0 ) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3];
            int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			if (matches != 3){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
            
            glm::vec3 normal_vector;
            
            normal_vector = computeFaceNormal(
                                        temp_vertices[vertexIndex[0] - 1],
                                        temp_vertices[vertexIndex[1] - 1],
                                        temp_vertices[vertexIndex[2] - 1]);
            out_normals.push_back(normal_vector);
             
            normal_vector = computeFaceNormal(
                                        temp_vertices[vertexIndex[1] - 1],
                                        temp_vertices[vertexIndex[2] - 1],
                                        temp_vertices[vertexIndex[0] - 1]);
            out_normals.push_back(normal_vector);
            
            normal_vector = computeFaceNormal(
                                        temp_vertices[vertexIndex[2] - 1],
                                        temp_vertices[vertexIndex[0] - 1],
                                        temp_vertices[vertexIndex[1] - 1]);
            out_normals.push_back(normal_vector);
            
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		out_vertices.push_back(vertex);
	}

	return true;
}

