#include "uSE_GLMesh.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>

#include "uSE_Quaternion.h"

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

    // file content containers
    int                  MD5Version;
    std::string          commandline;
    unsigned int         numJoints;
    unsigned int         numMeshes;
    std::vector< joint > joints;
    std::vector< mesh >  meshes;

    // tools to parse
    std::string          line;
    std::string          first_word_of_line;
    std::string          tmp;

    while( ! md5mesh_file.eof() )
    {
        first_word_of_line.clear();
        std::getline(md5mesh_file, line);
        std::stringstream ss(line);
        ss>>first_word_of_line;

        if(first_word_of_line == "MD5Version")
        {
            ss>>MD5Version;
        }
        else if(first_word_of_line == "commandline")
        {
            ss>>commandline;
        }
        else if(first_word_of_line == "numJoints")
        {
            ss>>numJoints;
        }
        else if(first_word_of_line == "numMeshes")
        {
            ss>>numMeshes;
        }
        else if(first_word_of_line == "joints")
        {
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
            }
        }
        else if(first_word_of_line == "mesh")
        {
            mesh current;

            // shader "name"
            md5mesh_file>>tmp>>current.shader;

            // numverts number
            md5mesh_file>>tmp>>current.numVerts;

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
            }

            // numtris number
            md5mesh_file>>tmp>>current.numTris;

            for(unsigned int i = 0; i < current.numTris; i++)
            {
                triangle current_triangle;

                md5mesh_file >> tmp
                             >> current_triangle.index
                             >> current_triangle.vert_index_0 >> current_triangle.vert_index_1 >> current_triangle.vert_index_2;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                current.triangles.push_back(current_triangle);
            }

            // numweights number
            md5mesh_file>>tmp>>current.numWeights;

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
            }

            meshes.push_back(current);
        }
    }
    md5mesh_file.close();

for(std::vector<mesh>::iterator it = meshes.begin(); it != meshes.end(); ++it)
{
    for(unsigned int i = 0; i < (*it).numVerts; i++)
    {
        uSE_GLVector vertex_pos;

        for(int j = 0; j < (*it).vertices.at(i).count_weight; j++)
        {
            weight curr_weight = (*it).weights.at((*it).vertices.at(i).start_weight + j);
            joint  curr_joint  = joints.at(curr_weight.joint);

            uSE_Quaternion rot_quat(0, uSE_GLVector(curr_joint.orient_x, curr_joint.orient_y, curr_joint.orient_z));
            rot_quat.computeReal();

            uSE_GLVector after_rot_pos = (rot_quat.conjugation() * uSE_Quaternion(1, uSE_GLVector(curr_weight.pos_x, curr_weight.pos_y, curr_weight.pos_z)) * rot_quat).get_vector();

            vertex_pos.set(vertex_pos.getX() + (curr_joint.pos_x + after_rot_pos.getX()) * curr_weight.bias,
                           vertex_pos.getY() + (curr_joint.pos_y + after_rot_pos.getY()) * curr_weight.bias,
                           vertex_pos.getZ() + (curr_joint.pos_z + after_rot_pos.getZ()) * curr_weight.bias);
        }

        m_vertices.push_back(vertex_pos.getX());
        m_vertices.push_back(vertex_pos.getY());
        m_vertices.push_back(vertex_pos.getZ());
    }

    // it seams that the md5mesh exporter in blender gives the faces in the wrong order
    for(unsigned int i = 0; i < (*it).numTris; i++)
    {
        m_indices.push_back((*it).triangles.at(i).vert_index_2);
        m_indices.push_back((*it).triangles.at(i).vert_index_1);
        m_indices.push_back((*it).triangles.at(i).vert_index_0);
    }

}

#if 0
    std::cout<<"MD5Version "<<MD5Version<<std::endl;
    std::cout<<"commandline "<<commandline<<std::endl<<std::endl;

    std::cout<<"numJoints "<<numJoints<<std::endl;
    std::cout<<"numMeshes "<<numMeshes<<std::endl<<std::endl;

    std::cout<<"joints {"<<std::endl;
        for(std::vector<joint>::iterator it = joints.begin(); it != joints.end(); ++it)
        {
            std::cout<<'\t'<<(*it).name<< " "<<(*it).parent<< " ( "<<(*it).pos_x<< " "<<(*it).pos_y<< " "<<(*it).pos_z<< " ) ( "<<(*it).orient_x<< " "<<(*it).orient_y<< " "<<(*it).orient_z<<" )"<<std::endl;
        }
    std::cout<<"}"<<std::endl<<std::endl;

    std::cout<<"mesh {"<<std::endl;
        for(std::vector<mesh>::iterator it = meshes.begin(); it != meshes.end(); ++it)
        {
            std::cout<<"\t shader "<<(*it).shader<<std::endl<<std::endl;

            std::cout<<"\t numverts "<<(*it).numVerts<<std::endl;
                for(std::vector<vertex>::iterator it_vertex = (*it).vertices.begin(); it_vertex != (*it).vertices.end(); ++it_vertex)
                {
                    std::cout<<"\t vert "<<(*it_vertex).index<< " ( "<<(*it_vertex).tex_s<<" "<<(*it_vertex).tex_t << " ) "<<(*it_vertex).start_weight<<" "<<(*it_vertex).count_weight<<std::endl;
                }
            std::cout<<std::endl;

            std::cout<<"\t numtris "<<(*it).numTris<<std::endl;
                for(std::vector<triangle>::iterator it_tris = (*it).triangles.begin(); it_tris != (*it).triangles.end(); ++it_tris)
                {
                    std::cout<<"\t tri "<<(*it_tris).index<< " "<<(*it_tris).vert_index_0<< " "<<(*it_tris).vert_index_1 << " "<<(*it_tris).vert_index_2<<std::endl;
                }
            std::cout<<std::endl;

            std::cout<<"\t numweights "<<(*it).numWeights<<std::endl;
            for(std::vector<weight>::iterator it_weights = (*it).weights.begin(); it_weights != (*it).weights.end(); ++it_weights)
            {
                std::cout<<"\t weight "<<(*it_weights).index<< " " << (*it_weights).joint << " " << (*it_weights).bias <<" ( " << (*it_weights).pos_x << " " << (*it_weights).pos_y << " " << (*it_weights).pos_z << " )" << std::endl;
            }
        }
    std::cout<<"}"<<std::endl;
#endif
}


struct hierarchy_joint
{
    std::string name;
    int         parent;
    int         flags;
    int         startIndex;
};

struct frame_bound
{
    float  min_x;
    float  min_y;
    float  min_z;
    float  max_x;
    float  max_y;
    float  max_z;
};

struct baseframe_joint
{
    float       pos_x;
    float       pos_y;
    float       pos_z;
    float       orient_x;
    float       orient_y;
    float       orient_z;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_GLMesh::parsemd5anim( const std::string& inFilename )
{
    std::ifstream md5anim_file(inFilename.c_str());
    assert(md5anim_file);

    // file content containers
    int                          MD5Version;
    std::string                  commandline;
    unsigned int                 numFrames;
    unsigned int                 numJoints;
    unsigned int                 frameRate;
    unsigned int                 numAnimatedComponents;
    std::vector<hierarchy_joint> hierarchy;
    std::vector<frame_bound>     bounds;
    std::vector<baseframe_joint> baseframe;
    std::map< unsigned int, std::vector<float> > frames;
    // tools to parse
    std::string          line;
    std::string          first_word_of_line;
    std::string          tmp;

    while( ! md5anim_file.eof() )
    {
        first_word_of_line.clear();
        std::getline(md5anim_file, line);
        std::stringstream ss(line);
        ss>>first_word_of_line;

        if(first_word_of_line == "MD5Version")
        {
            ss>>MD5Version;
        }
        else if(first_word_of_line == "commandline")
        {
            ss>>commandline;
        }
        else if(first_word_of_line == "numFrames")
        {
            ss>>numFrames;
        }
        else if(first_word_of_line == "numJoints")
        {
            ss>>numJoints;
        }
        else if(first_word_of_line == "frameRate")
        {
            ss>>frameRate;
        }
        else if(first_word_of_line == "numAnimatedComponents")
        {
            ss>>numAnimatedComponents;
        }
        else if(first_word_of_line == "hierarchy")
        {
            for(unsigned int i = 0; i < numJoints; i++)
            {
                hierarchy_joint current;

                md5anim_file >>current.name
                             >>current.parent>>current.flags>>current.startIndex;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5anim_file, tmp);

                hierarchy.push_back(current);
            }
        }
        else if(first_word_of_line == "bounds")
        {
            for(unsigned int i = 0; i < numFrames; i++)
            {
                frame_bound current;

                char bracket;
                md5anim_file >>bracket>>current.min_x>>current.min_y>>current.min_z>>bracket
                             >>bracket>>current.max_x>>current.max_y>>current.max_z>>bracket;

                bounds.push_back(current);
            }
        }
        else if(first_word_of_line == "baseframe")
        {
            for(unsigned int i = 0; i < numJoints; i++)
            {
                baseframe_joint current;

                char bracket;
                md5anim_file >>bracket>>current.pos_x>>current.pos_y>>current.pos_z>>bracket
                             >>bracket>>current.orient_x>>current.orient_y>>current.orient_z>>bracket;

                baseframe.push_back(current);
            }
        }
        else if(first_word_of_line == "frame")
        {
            unsigned int current_index;

            ss>>current_index;

            std::vector<float> current_frame;

            for(unsigned int i = 0; i < numAnimatedComponents; i++)
            {
                float current_element;
                md5anim_file>>current_element;

                current_frame.push_back(current_element);
            }
            frames.insert(std::make_pair(current_index, current_frame));
        }
    }

#if 0
    std::cout<<"MD5Version "<<MD5Version<<std::endl;
    std::cout<<"commandline "<<commandline<<std::endl<<std::endl;

    std::cout<<"numFrames "<<numFrames<<std::endl;
    std::cout<<"numJoints "<<numJoints<<std::endl;
    std::cout<<"frameRate "<<frameRate<<std::endl;
    std::cout<<"numAnimatedComponents "<<numAnimatedComponents<<std::endl<<std::endl;

    std::cout<<"hierarchy {"<<std::endl;
        for(std::vector<hierarchy_joint>::iterator it_hj = hierarchy.begin(); it_hj != hierarchy.end(); ++it_hj)
        {
            std::cout<<"\t "<<(*it_hj).name<<"\t"<<(*it_hj).parent<<" "<<(*it_hj).flags<<" "<<(*it_hj).startIndex<<std::endl;
        }
    std::cout<<"}"<<std::endl<<std::endl;

    std::cout<<"bounds {"<<std::endl;
        for(std::vector<frame_bound>::iterator it_fb = bounds.begin(); it_fb != bounds.end(); ++it_fb)
        {
            std::cout<<"\t( "<<(*it_fb).min_x<<" "<<(*it_fb).min_y<<" "<<(*it_fb).min_z<<" ) ( "
                     <<(*it_fb).max_x<<" "<<(*it_fb).max_y<<" "<<(*it_fb).max_z<<" )"<<std::endl;
        }
    std::cout<<"}"<<std::endl<<std::endl;

    std::cout<<"baseframe {"<<std::endl;
        for(std::vector<baseframe_joint>::iterator it_bfj = baseframe.begin(); it_bfj != baseframe.end(); ++it_bfj)
        {
            std::cout<<"\t ( "<<(*it_bfj).pos_x<<" "<<(*it_bfj).pos_y<<" "<<(*it_bfj).pos_z<<" ) ( "
                     << (*it_bfj).orient_x<< " "<<(*it_bfj).orient_y<<" "<<(*it_bfj).orient_z<<" )"<<std::endl;
        }
    std::cout<<"}"<<std::endl<<std::endl;

    for(std::map<unsigned int, std::vector<float> >::iterator it = frames.begin(); it != frames.end(); ++it)
    {
        std::cout<<"frame "<<(*it).first<<" {";
        for(unsigned int i = 0; i < (*it).second.size(); ++i)
        {
            i%6 == 0 ? std::cout<<std::endl<<'\t' : std::cout<<" ";
            std::cout<<(*it).second.at(i);
        }
        std::cout<<std::endl<<"}"<<std::endl<<std::endl;
    }
#endif
}
