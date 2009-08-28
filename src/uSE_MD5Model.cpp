#include "uSE_MD5Model.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_MD5Model::uSE_MD5Model()
{

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_MD5Model::~uSE_MD5Model()
{

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_MD5Model::parsemd5mesh( const std::string& inFilename )
{
    std::ifstream md5mesh_file(inFilename.c_str());
    assert(md5mesh_file);

    // tools for mesh parsing, useless to store...(for now ?)
    int                  MD5Version;
    std::string          commandline;
    unsigned int         numJoints;
    unsigned int         numMeshes;


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
                char bracket;
                std::string tmp_name;
                int tmp_parent;

                float tmp_pos_x;
                float tmp_pos_y;
                float tmp_pos_z;

                float tmp_orient_x;
                float tmp_orient_y;
                float tmp_orient_z;

                md5mesh_file >> tmp_name
                             >> tmp_parent
                             >> bracket
                             >> tmp_pos_x >> tmp_pos_y >> tmp_pos_z
                             >> bracket >> bracket
                             >> tmp_orient_x >> tmp_orient_y >> tmp_orient_z
                             >> bracket;

                uSE_GLVector tmp_position(tmp_pos_x, tmp_pos_y, tmp_pos_z);

                uSE_Quaternion tmp_orientation(0, uSE_GLVector(tmp_orient_x, tmp_orient_y, tmp_orient_z));
                tmp_orientation.computeReal();

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                uSE_Joint current(tmp_name, tmp_parent, tmp_position, tmp_orientation);
                m_joints.push_back(current);
            }
        }
        else if(first_word_of_line == "mesh")
        {
            uSE_Mesh current;

            md5mesh_file>>tmp;

            while(tmp != "shader")
            {
                std::getline(md5mesh_file, tmp);
                md5mesh_file>>tmp;
            }

            // shader "name"
            std::string tmp_shader_name;
            md5mesh_file>>tmp_shader_name;

            // numverts number
            int tmp_vertex_number;
            md5mesh_file>>tmp>>tmp_vertex_number;

            for(int i = 0; i < tmp_vertex_number; i++)
            {
                int tmp_index;

                float tmp_s;
                float tmp_t;

                int tmp_startweight_index;
                int tmp_countweight;

                char bracket;
                md5mesh_file >> tmp >> tmp_index
                             >> bracket >> tmp_s >> tmp_t >> bracket
                             >> tmp_startweight_index >> tmp_countweight;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                uSE_Vertex current_vertex(tmp_s, tmp_t, tmp_startweight_index, tmp_countweight);
                current.add_vertex(current_vertex);
            }

            // numtris number
            int tmp_triangle_number;
            md5mesh_file>>tmp>>tmp_triangle_number;

            for(int i = 0; i < tmp_triangle_number; i++)
            {
                int tmp_index;
                int tmp_first_position_index;
                int tmp_second_position_index;
                int tmp_third_position_index;

                md5mesh_file >> tmp
                             >> tmp_index
                             >> tmp_first_position_index >> tmp_second_position_index >> tmp_third_position_index;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                uSE_Triangle current_triangle(tmp_first_position_index, tmp_second_position_index, tmp_third_position_index);
                current.add_triangle(current_triangle);
            }

            // numweights number
            int tmp_weight_number;
            md5mesh_file>>tmp>>tmp_weight_number;

            for(int i = 0; i < tmp_weight_number; i++)
            {
                int tmp_index;
                int tmp_depending_joint;

                float tmp_bias;

                float tmp_pos_x;
                float tmp_pos_y;
                float tmp_pos_z;

                char bracket;
                md5mesh_file >> tmp
                             >> tmp_index
                             >> tmp_depending_joint
                             >> tmp_bias
                             >> bracket >> tmp_pos_x >> tmp_pos_y >> tmp_pos_z >> bracket;

                uSE_GLVector tmp_position(tmp_pos_x, tmp_pos_y, tmp_pos_z);

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5mesh_file, tmp);

                uSE_Weight current_weight(tmp_depending_joint, tmp_bias, tmp_position);
                current.add_weight(current_weight);
            }

            m_meshes.push_back(current);
        }
    }
    md5mesh_file.close();

#if 0
    std::cout<<"MD5Version "<<MD5Version<<std::endl;
    std::cout<<"commandline "<<commandline<<std::endl<<std::endl;

    std::cout<<"numJoints "<<numJoints<<std::endl;
    std::cout<<"numMeshes "<<numMeshes<<std::endl<<std::endl;

    std::cout<<"joints {"<<std::endl;
        for(std::vector<uSE_Joint>::iterator it = m_joints.begin(); it != m_joints.end(); ++it)
        {
            std::cout<<std::fixed<</'\t'<<it->getName()<< " "<<it->getParentIndex()<< " ( "<<it->getPosition().getX()<< " "<<it->getPosition().getY()<< " "<<it->getPosition().getZ()<< " ) ( "<<it->getOrientation().get_vector().getX()<< " "<<it->getOrientation().get_vector().getY()<< " "<<it->getOrientation().get_vector().getZ()<<" )"<<std::endl;
        }
    std::cout<<"}"<<std::endl<<std::endl;

    std::cout<<"mesh {"<<std::endl;
        for(std::vector<uSE_Mesh>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
        {
            std::cout<<"\t shader "<<it->getShaderName()<<std::endl<<std::endl;

            unsigned int numverts = it->getVerticesCount();
            std::cout<<"\t numverts "<<numverts<<std::endl;
                for(unsigned int i = 0; i < numverts; i++)
                {
                    uSE_Vertex curr_vert = it->getVertexAtIndex(i);
                    std::cout<<"\t vert "<<i<< " ( "<<curr_vert.getSCoord()<<" "<<curr_vert.getTCoord() << " ) "<<curr_vert.getStartWeightIndex()<<" "<<curr_vert.getCountWeight()<<std::endl;
                }
            std::cout<<std::endl;

            unsigned int numtris = it->getTrianglesCount();
            std::cout<<"\t numtris "<<numtris<<std::endl;
                for(unsigned int i = 0; i < numtris; i++)
                {
                    uSE_Triangle curr_tri = it->getTriangleAtIndex(i);
                    std::cout<<"\t tri "<<i<< " "<<curr_tri.getFirstPositionIndex()<< " "<<curr_tri.getSecondPositionIndex()<< " "<<curr_tri.getThirdPositionIndex()<<std::endl;
                }
            std::cout<<std::endl;

            unsigned int numweights = it->getWeightsCount();
            std::cout<<"\t numweights "<<numweights<<std::endl;
            for(unsigned int i = 0; i < numweights; i++)
            {
                uSE_Weight curr_weight = it->getWeightAtIndex(i);
                std::cout<<"\t weight "<<i<< " " << curr_weight.getDependingJoint() << " " << curr_weight.getBiasFactor() <<" ( " << curr_weight.getPosition().getX() << " " << curr_weight.getPosition().getY() << " " << curr_weight.getPosition().getZ() << " )" << std::endl;
            }
        }
    std::cout<<"}"<<std::endl;
#endif
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_MD5Model::parsemd5anim( const std::string& inFilename )
{
    std::ifstream md5anim_file(inFilename.c_str());
    assert(md5anim_file);

    uSE_Animation curr_animation(inFilename);

    // tools for anim parsing, useless to store...(for now ?)
    int                          MD5Version;
    std::string                  commandline;
    unsigned int                 numFrames;
    unsigned int                 numJoints;
    int                          numAnimatedComponents;

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
            curr_animation.setNbFrames(numFrames);
        }
        else if(first_word_of_line == "numJoints")
        {
            ss>>numJoints;
        }
        else if(first_word_of_line == "frameRate")
        {
            int frameRate;
            ss>>frameRate;
            curr_animation.setFrameRateFPS(frameRate);
        }
        else if(first_word_of_line == "numAnimatedComponents")
        {
            ss>>numAnimatedComponents;
            curr_animation.setNbAnimatedComponents(numAnimatedComponents);
        }
        else if(first_word_of_line == "hierarchy")
        {
            for(unsigned int i = 0; i < numJoints; i++)
            {
                std::string tmp_name;
                int         tmp_parent_index;
                int         tmp_flags;
                int         tmp_data_start_index;

                md5anim_file >> tmp_name
                             >> tmp_parent_index >> tmp_flags >> tmp_data_start_index;

                // if the last element asked from the stream is not a string, then it leaves \n
                std::getline(md5anim_file, tmp);

                uSE_AnimJoint current(tmp_name, tmp_parent_index, tmp_flags, tmp_data_start_index);
                curr_animation.addAnimJoint(current);
            }
        }
        else if(first_word_of_line == "bounds")
        {
            for(unsigned int i = 0; i < numFrames; i++)
            {
                float tmp_min_x, tmp_min_y, tmp_min_z;
                float tmp_max_x, tmp_max_y, tmp_max_z;

                char bracket;
                md5anim_file >>bracket>>tmp_min_x>>tmp_min_y>>tmp_min_z>>bracket
                             >>bracket>>tmp_max_x>>tmp_max_y>>tmp_max_z>>bracket;

                uSE_GLVector tmp_min(tmp_min_x, tmp_min_y, tmp_min_z);
                uSE_GLVector tmp_max(tmp_max_x, tmp_max_y, tmp_max_z);

                uSE_BoundBox current(tmp_min, tmp_max);
                curr_animation.addBoundBox(current);
            }
        }
        else if(first_word_of_line == "baseframe")
        {
            for(unsigned int i = 0; i < numJoints; i++)
            {
                float tmp_pos_x, tmp_pos_y, tmp_pos_z;
                float tmp_orient_x, tmp_orient_y, tmp_orient_z;

                char bracket;
                md5anim_file >>bracket>>tmp_pos_x>>tmp_pos_y>>tmp_pos_z>>bracket
                             >>bracket>>tmp_orient_x>>tmp_orient_y>>tmp_orient_z>>bracket;

                uSE_GLVector tmp_position(tmp_pos_x, tmp_pos_y, tmp_pos_z);

                uSE_Quaternion tmp_orientation(0, uSE_GLVector(tmp_orient_x, tmp_orient_y, tmp_orient_z));
                tmp_orientation.computeReal();

                uSE_Joint current("", -1, tmp_position, tmp_orientation);

                curr_animation.addBaseFrameJoint(current);
            }
        }
        else if(first_word_of_line == "frame")
        {
            unsigned int current_index;

            ss>>current_index;

            std::vector<float> current_frame;

            for(int i = 0; i < numAnimatedComponents; i++)
            {
                float current_element;
                md5anim_file>>current_element;

                current_frame.push_back(current_element);
            }
            curr_animation.addFrameData(current_frame);
        }
    }
    m_animations.push_back(curr_animation);

#if 0
    for(std::vector<uSE_Animation>::iterator it_animation_file = m_animations.begin(); it_animation_file != m_animations.end(); ++it_animation_file)
    {
        std::cout<<"MD5Version "<<MD5Version<<std::endl;
        std::cout<<"commandline "<<commandline<<std::endl<<std::endl;

        std::cout<<"numFrames "<<numFrames<<std::endl;
        std::cout<<"numJoints "<<numJoints<<std::endl;
        std::cout<<"frameRate "<<it_animation_file->getFrameRateFPS()<<std::endl;
        int nb_animated_components = it_animation_file->getNbAnimatedComponents();
        std::cout<<"numAnimatedComponents "<<nb_animated_components<<std::endl<<std::endl;

        std::cout<<"hierarchy {"<<std::endl;
            for(unsigned int i = 0; i < numJoints; ++i)
            {
                uSE_AnimJoint curr_joint = it_animation_file->getAnimJointAtIndex(i);
                std::cout<<std::fixed<<"\t "<<curr_joint.getName()<<"\t"<<curr_joint.getParentIndex()<<" "<<curr_joint.getFlags()<<" "<<curr_joint.getDataStartIndex()<<std::endl;
            }
        std::cout<<"}"<<std::endl<<std::endl;

        std::cout<<"bounds {"<<std::endl;
            for(unsigned int i = 0; i < numFrames; ++i)
            {
                uSE_BoundBox curr_boundbox = it_animation_file->getBoundBoxAtIndex(i);
                std::cout<<"\t( "<< curr_boundbox.getMin().getX()<<" "<<curr_boundbox.getMin().getY()<<" "<<curr_boundbox.getMin().getZ()<<" ) ( "
                         <<         curr_boundbox.getMax().getX()<<" "<<curr_boundbox.getMax().getY()<<" "<<curr_boundbox.getMax().getZ()<<" )"<<std::endl;
            }
        std::cout<<"}"<<std::endl<<std::endl;

        std::cout<<"baseframe {"<<std::endl;
            for(unsigned int i = 0; i < numJoints; ++i)
            {
                uSE_Joint curr_baseframe_joint = it_animation_file->getBaseFrameJointAtIndex(i);
                std::cout<<"\t ( "<<curr_baseframe_joint.getPosition().getX()<<" "<<curr_baseframe_joint.getPosition().getY()<<" "<<curr_baseframe_joint.getPosition().getZ()<<" ) ( "
                        << curr_baseframe_joint.getOrientation().get_vector().getX()<< " "<<curr_baseframe_joint.getOrientation().get_vector().getY()<<" "<<curr_baseframe_joint.getOrientation().get_vector().getZ()<<" )"<<std::endl;
            }
        std::cout<<"}"<<std::endl<<std::endl;

        for(unsigned int i = 0; i < numFrames; ++i)
        {
            std::cout<<"frame "<<i<<" {";
            for(int j = 0; j < nb_animated_components; ++j)
            {
                j%6 == 0 ? std::cout<<std::endl<<'\t' : std::cout<<" ";
                std::cout<<it_animation_file->getFrameComponentFromFrameAtIndex(i,j);
            }
            std::cout<<std::endl<<"}"<<std::endl<<std::endl;
        }
    }
#endif
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_MD5Model::generateVerticesIndicesPose()
{
    m_pose_vertices.clear();
    m_pose_indices.clear();

    int decal = 0;
    int old_vx_nb = 0;

    for(std::vector<uSE_Mesh>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
    {
        unsigned int numVerts = it->getVerticesCount();
        for(unsigned int i = 0; i < numVerts; i++)
        {
            uSE_GLVector vertex_pos;

            uSE_Vertex curr_vertex = it->getVertexAtIndex(i);

            // nb of weights associated to current vertex
            int vertex_count_weight = curr_vertex.getCountWeight();

            for(int j = 0; j < vertex_count_weight; j++)
            {
                uSE_Weight curr_weight = it->getWeightAtIndex(curr_vertex.getStartWeightIndex() + j);
                uSE_Joint  curr_joint  = m_joints.at(curr_weight.getDependingJoint());

                // real part already computed
                uSE_Quaternion rot_quat = curr_joint.getOrientation();

                uSE_GLVector after_rot_pos = (rot_quat.conjugation() * uSE_Quaternion(1, curr_weight.getPosition()) * rot_quat).get_vector();

                vertex_pos = vertex_pos + (curr_joint.getPosition() + after_rot_pos) * curr_weight.getBiasFactor();
            }
            m_pose_vertices.push_back(vertex_pos.getX());
            m_pose_vertices.push_back(vertex_pos.getY());
            m_pose_vertices.push_back(vertex_pos.getZ());
        }

        unsigned int numTris = it->getTrianglesCount();

        // it seams that the md5mesh exporter in blender gives the faces in the wrong order
        for(unsigned int i = 0; i < numTris; i++)
        {
            uSE_Triangle curr_tri = it->getTriangleAtIndex(i);

            m_pose_indices.push_back(curr_tri.getThirdPositionIndex()  + decal * old_vx_nb);
            m_pose_indices.push_back(curr_tri.getSecondPositionIndex() + decal * old_vx_nb);
            m_pose_indices.push_back(curr_tri.getFirstPositionIndex()  + decal * old_vx_nb);
        }
        old_vx_nb = numVerts;
        decal++;
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_MD5Model::generateVerticesIndicesFromAnimAtFrame( const unsigned int inAnim, const unsigned int inFrame )
{
    assert(inAnim < m_animations.size());

    m_frames_vertices[inAnim].clear();
    m_frames_indices [inAnim].clear();

    uSE_Animation curr_animation = m_animations.at(inAnim);

    assert(inFrame < curr_animation.getNbFrames());

    for(unsigned int i = 0; i < curr_animation.getAnimJointsNb(); ++i)
    {
        uSE_Joint current_joint = curr_animation.getBaseFrameJointAtIndex(i);

        uSE_AnimJoint curr_anim_joint = curr_animation.getAnimJointAtIndex(i);

        uSE_GLVector   animatedPosition    = current_joint.getPosition();
        uSE_Quaternion animatedOrientation = current_joint.getOrientation();

        int step = 0;

        int curr_flags = curr_anim_joint.getFlags();
        if(curr_flags & 1)
        {
            animatedPosition.setX(curr_animation.getFrameComponentFromFrameAtIndex(inFrame, curr_anim_joint.getDataStartIndex() + step));
            step++;
        }
        if(curr_flags & 2)
        {
            animatedPosition.setY(curr_animation.getFrameComponentFromFrameAtIndex(inFrame, curr_anim_joint.getDataStartIndex() + step));
            step++;
        }
        if(curr_flags & 4)
        {
            animatedPosition.setZ(curr_animation.getFrameComponentFromFrameAtIndex(inFrame, curr_anim_joint.getDataStartIndex() + step));
            step++;
        }

        if(curr_flags & 8)
        {
            animatedOrientation.set_vector(uSE_GLVector(curr_animation.getFrameComponentFromFrameAtIndex(inFrame, curr_anim_joint.getDataStartIndex() + step), animatedOrientation.get_vector().getY(), animatedOrientation.get_vector().getZ()));
            step++;
        }
        if(curr_flags & 16)
        {
            animatedOrientation.set_vector(uSE_GLVector(animatedOrientation.get_vector().getX(), curr_animation.getFrameComponentFromFrameAtIndex(inFrame, curr_anim_joint.getDataStartIndex() + step), animatedOrientation.get_vector().getZ()));
            step++;
        }
        if(curr_flags & 32)
        {
            animatedOrientation.set_vector(uSE_GLVector(animatedOrientation.get_vector().getX(), animatedOrientation.get_vector().getY(), curr_animation.getFrameComponentFromFrameAtIndex(inFrame, curr_anim_joint.getDataStartIndex() + step)));
            step++;
        }
        animatedOrientation.computeReal();



        uSE_Joint currentSkelJoint;
        currentSkelJoint.setName(curr_anim_joint.getName());
        currentSkelJoint.setParentIndex(curr_anim_joint.getParentIndex());

        if(currentSkelJoint.getParentIndex() < 0)
        {
            currentSkelJoint.setPosition(animatedPosition);
            currentSkelJoint.setOrientation(animatedOrientation);
#warning create map for joints per frame
        }
        else
        {
            uSE_Joint parentSkelJoint = m_joints.at(currentSkelJoint.getParentIndex());

            uSE_Quaternion rot_quat = parentSkelJoint.getOrientation();

            uSE_GLVector rotatedPos = (rot_quat.conjugation() * uSE_Quaternion(1, animatedPosition) * rot_quat).get_vector();

            currentSkelJoint.setPosition(parentSkelJoint.getPosition() + rotatedPos );

            uSE_Quaternion rotatedOrient = animatedOrientation * rot_quat;

            currentSkelJoint.setOrientation(rotatedOrient);
        }
        m_joints.at(i) = currentSkelJoint;
    }
}
