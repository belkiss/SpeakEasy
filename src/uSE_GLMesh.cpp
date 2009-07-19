#include "uSE_GLMesh.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMesh::uSE_GLMesh()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMesh::~uSE_GLMesh()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_GLMesh::display()
{
    for ( unsigned int i = 0; i < m_triangles.size(); i++ )
    {
        m_triangles.at( i ).display();
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_GLMesh::parseobj( std::string inFilename )
{

    uSE_GLMesh currentmesh;
    bool firstmesh = 1;

    //////////////////////////////////////////////////////////////////////////
    //variables used for material
    std::string mtltouse;
    //////////////////////////////////////////////////////////////////////////

    std::ifstream filed;
    filed.open( inFilename.c_str(), std::ios::in );
    assert( filed.good() );
    char UnChar;

    while ( filed.good() && ! filed.eof() )
    {
        if ( !( filed.get( UnChar ) ).fail() )
        {
            if ( UnChar == '#' || UnChar == 's' )
            {
                filed.ignore( 255, '\n' );
            }
            else
            {
                if ( UnChar == 'g' )
                {
                    std::string groupname;
                    filed >> groupname;
                }
                else if ( UnChar == 'o' )
                {
                    firstmesh = 0;
                    std::string objectname;
                    filed >> objectname;
                }
                else if ( UnChar == 'm' )
                {
                    std::string mtllibname;
                    filed >> mtllibname;

                    while ( filed.peek() == ' '  || filed.peek() == '\r' ) filed.get();

                    if ( mtllibname == "tllib" )
                        filed >> mtllibname;

                    std::string tmp;

                    while ( mtllibname.rfind( ".mtl" ) == std::string::npos )
                    {
                        filed >> tmp;
                        mtllibname += " ";
                        mtllibname += tmp;
                    }
                }
                else if ( UnChar == 'u' )
                {
                    std::string oldmtl = mtltouse;
                    filed >> mtltouse;

                    while ( filed.peek() == ' ' || filed.peek() == '\r') filed.get();

                    if ( mtltouse == "semtl" )
                        filed >> mtltouse;

                }
                else if ( UnChar == 'v' )
                {
                    if ( filed.peek() == ' ' ) // vertex
                    {
                        float x;
                        float y;
                        float z;
                        float w = 1.0;
                        filed >> x >> y >> z;

                        // test if the 4th coordinate is given (w)
                        while ( filed.peek() == ' ' || filed.peek() == '\r')
                            filed.get();
                        if ( filed.peek() != '\n' ) {filed >> w;}

                        m_vertices.push_back( x ); // x
                        m_vertices.push_back( y ); // y
                        m_vertices.push_back( z ); // z
                    }
                    else if ( filed.peek() == 'n' ) //normal
                    {
                        filed.get();
                        float x;
                        float y;
                        float z;
                        filed >> x >> y >> z;
                    }
                    else if ( filed.peek() == 't' ) //texture
                    {
                        filed.get();
                        float x;
                        float y = 0;
                        float z = 0;
                        filed >> x;

                        //test if we have a 2nd coordinate :
                        while ( filed.peek() == ' ' || filed.peek() == '\r') filed.get();
                        if ( filed.peek() != '\n' ) {filed >> y;}

                        //test if we have a 3rd coordinate :
                        while ( filed.peek() == ' ' || filed.peek() == '\r') filed.get();
                        if ( filed.peek() != '\n' ) {filed >> z;}
                    }
                }
                else if ( UnChar == 'f' )
                {
                    char slash;
                    uSE_GLTriangle currentface;

                    while ( filed.peek() != '\n' && !filed.eof() )
                    {
                        int tmp;
                        filed >> tmp;

                        m_indices.push_back( tmp - 1 );
                        if ( filed.peek() == '/' )
                        {
                            filed >> slash;

                            //test if we have a texture coordinate :
                            if ( filed.peek() != '/' )
                            {
                                filed >> tmp;
                            }
                            else
                            {
                                tmp = 0;
                            }

                            bool slashfound = 0;
                            if ( filed.peek() == '/' )
                            {
                                slashfound = 1;
                                filed >> slash;
                            }

                            if ( filed.peek() != ' ' && filed.peek() != '\n' )
                            {
                                filed >> tmp;
                            }
                            else
                            {
                                tmp = 0;
                            }
                        }
                        while ( filed.peek() == ' ' || filed.peek() == '\r' ) filed.get();
                    }
                }
            }
        }
    }
    filed.close();
}


struct joint
{
    std::string name;
    int         parent;
    float       pos_x;
    float       pos_y;
    float       pos_z;
    float       orient_x;
    float       orient_y;
    float       orient_z;
};

struct vertex
{
    int   index;
    float tex_s;
    float tex_t;
    int   start_weight;
    int   count_weight;
};

struct triangle
{
    int index;
    int vert_index_0;
    int vert_index_1;
    int vert_index_2;
};

struct weight
{
    int   index;
    int   joint;
    float bias;
    float pos_x;
    float pos_y;
    float pos_z;
};

struct mesh
{
    std::string           shader;
    unsigned int          numVerts;
    std::vector<vertex>   vertices;
    unsigned int          numTris;
    std::vector<triangle> triangles;
    unsigned int          numWeights;
    std::vector<weight>   weights;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_GLMesh::parsemd5mesh( const std::string& inFilename )
{
    std::ifstream md5mesh_file(inFilename.c_str());
    assert(md5mesh_file);

    int MD5Version;
    std::string commandline;
    unsigned int numJoints;
    unsigned int numMeshes;

    std::vector< joint > joints;
    std::string line;
    std::string first_word_of_line;

    std::string tmp;

    while( ! md5mesh_file.eof() )
    {
        first_word_of_line.clear();
        std::getline(md5mesh_file, line);
        std::stringstream ss(line);
        ss>>first_word_of_line;

        if(first_word_of_line == "MD5Version")
        {
            ss>>MD5Version;

            std::cout<<"MD5Version "<<MD5Version<<std::endl;
        }
        else if(first_word_of_line == "commandline")
        {
            ss>>commandline;
        
            std::cout<<"commandline "<<commandline<<std::endl<<std::endl;
        }
        else if(first_word_of_line == "numJoints")
        {
            ss>>numJoints;

            std::cout<<"numJoints "<<numJoints<<std::endl;
        }
        else if(first_word_of_line == "numMeshes")
        {
            ss>>numMeshes;

            std::cout<<"numMeshes "<<numMeshes<<std::endl<<std::endl;
        }
        else if(first_word_of_line == "joints")
        {
            std::cout<<"joints {"<<std::endl;
            for(unsigned int i = 0; i < numJoints; i++)
            {
                joint current;

                char bracket;
                md5mesh_file >>current.name
                            >>current.parent>>bracket>>current.pos_x>>current.pos_y>>current.pos_z>>bracket
                            >>bracket>>current.orient_x>>current.orient_y>>current.orient_z>>bracket;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                joints.push_back(current);

                std::cout<<'\t'<<current.name<< " "<<current.parent<< " ( "<<current.pos_x<< " "<<current.pos_y<< " "<<current.pos_z<< " ) ( "<<current.orient_x<< " "<<current.orient_y<< " "<<current.orient_z<<" )"<<std::endl;
            }
            std::cout<<"}"<<std::endl<<std::endl;
        }
        else if(first_word_of_line == "mesh")
        {
            std::cout<<"mesh {"<<std::endl;
            mesh current;

            // shader "name"
            md5mesh_file>>tmp>>current.shader;

            std::cout<<"\t shader "<<current.shader<<std::endl<<std::endl;

            // numverts number
            md5mesh_file>>tmp>>current.numVerts;

            std::cout<<"\t numverts "<<current.numVerts<<std::endl;
            for(unsigned int i = 0; i < current.numVerts; i++)
            {
                vertex current_vertex;

                char bracket;
                md5mesh_file >> tmp >> current_vertex.index
                             >> bracket >> current_vertex.tex_s >> current_vertex.tex_t >> bracket
                             >> current_vertex.start_weight >> current_vertex.count_weight;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                current.vertices.push_back(current_vertex);

                std::cout<<"\t vert "<<current_vertex.index<< " ( "<<current_vertex.tex_s<<" "<<current_vertex.tex_t << " ) "<<current_vertex.start_weight<<" "<<current_vertex.count_weight<<std::endl;
            }
            std::cout<<std::endl;

            // numtris number
            md5mesh_file>>tmp>>current.numTris;

            std::cout<<"\t numtris "<<current.numTris<<std::endl;
            for(unsigned int i = 0; i < current.numTris; i++)
            {
                triangle current_triangle;

                md5mesh_file >> tmp
                             >> current_triangle.index
                             >> current_triangle.vert_index_0 >> current_triangle.vert_index_1 >> current_triangle.vert_index_2;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                current.triangles.push_back(current_triangle);

                std::cout<<"\t tri "<<current_triangle.index<< " "<<current_triangle.vert_index_0<< " "<<current_triangle.vert_index_1 << " "<<current_triangle.vert_index_2<<std::endl;
            }
            std::cout<<std::endl;

            // numweights number
            md5mesh_file>>tmp>>current.numWeights;

            std::cout<<"\t numweights "<<current.numWeights<<std::endl;
            for(unsigned int i = 0; i < current.numWeights; i++)
            {
                weight current_weight;

                char bracket;
                md5mesh_file >> tmp
                             >> current_weight.index
                             >> current_weight.joint
                             >> current_weight.bias
                             >> bracket >> current_weight.pos_x >> current_weight.pos_y >> current_weight.pos_z >> bracket;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                current.weights.push_back(current_weight);

                std::cout<<"\t weight "<<current_weight.index<< " " << current_weight.joint << " " << current_weight.bias <<" ( " << current_weight.pos_x << " " << current_weight.pos_y << " " << current_weight.pos_z << " )" << std::endl;
            }
            std::cout<<"}"<<std::endl;
        }
    }
    md5mesh_file.close();
}
