/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2012-2013 Lambert Clara <lambert.clara@yahoo.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file    SE_CRenderManager.h
 * @brief   3d Rendering Manager
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2012-07-01
 */

#ifndef SE_CRENDERMANAGER_H
#define SE_CRENDERMANAGER_H

#include "SE_IBaseManager.h"

class SE_CRenderManager : public SE_IBaseManager
{
    public:
        SE_CRenderManager();
        ~SE_CRenderManager(){}

        bool startUp()  override;
        bool shutDown() override;

        void render();

    private:
        void createVBO();
        void destroyVBO();

        void createShaders();
        void destroyShaders();

        void logGLerror(char const * const inpDescriptionText) const;

    private:
        U32 m_vertexShaderId;
        U32 m_fragmentShaderId;
        U32 m_programId;
        U32 m_vertexArrayObjectId;
        U32 m_vertexBufferObjectId;
        U32 m_colorBufferId;
};

#endif // SE_CRENDERMANAGER_H
