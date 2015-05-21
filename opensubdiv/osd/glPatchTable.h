//
//   Copyright 2015 Pixar
//
//   Licensed under the Apache License, Version 2.0 (the "Apache License")
//   with the following modification; you may not use this file except in
//   compliance with the Apache License and the following modification to it:
//   Section 6. Trademarks. is deleted and replaced with:
//
//   6. Trademarks. This License does not grant permission to use the trade
//      names, trademarks, service marks, or product names of the Licensor
//      and its affiliates, except as required to comply with Section 4(c) of
//      the License and to reproduce the content of the NOTICE file.
//
//   You may obtain a copy of the Apache License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the Apache License with the above modification is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
//   KIND, either express or implied. See the Apache License for the specific
//   language governing permissions and limitations under the Apache License.
//

#ifndef OPENSUBDIV3_OSD_GL_PATCH_TABLE_H
#define OPENSUBDIV3_OSD_GL_PATCH_TABLE_H

#include "../version.h"

#include <vector>
#include "../far/patchDescriptor.h"
#include "../osd/nonCopyable.h"
#include "../osd/opengl.h"

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

namespace Far{
    class PatchTables;
};

namespace Osd {

class GLPatchTable : private NonCopyable<GLPatchTable> {
public:
    typedef GLuint VertexBufferBinding;

    // XXX: this struct will be further refactored.
    class PatchArray {
    public:
        PatchArray(Far::PatchDescriptor desc, int numPatches,
                   int indexBase, int primitiveIdBase) :
            desc(desc), numPatches(numPatches), indexBase(indexBase),
            primitiveIdBase(primitiveIdBase) {}
        Far::PatchDescriptor const &GetDescriptor() const {
            return desc;
        }
        int GetNumPatches() const {
            return numPatches;
        }
        int GetIndexBase() const {
            return indexBase;
        }
        int GetPrimitiveIdBase() const {
            return primitiveIdBase;
        }
    private:
        Far::PatchDescriptor desc;
        int numPatches;
        int indexBase;        // an offset within the index buffer
        int primitiveIdBase;  // an offset within the patch param buffer
    };
    typedef std::vector<PatchArray> PatchArrayVector;

    GLPatchTable();
    ~GLPatchTable();

    static GLPatchTable *Create(Far::PatchTables const *farPatchTables,
                                void *deviceContext = NULL);

    PatchArrayVector const &GetPatchArrays() const {
        return _patchArrays;
    }

    /// Returns the GL index buffer containing the patch control vertices
    GLuint GetPatchIndexBuffer() const {
        return _indexBuffer;
    }

    /// Returns the GL texture buffer containing the patch parameter
    GLuint GetPatchParamTextureBuffer() const {
        return _patchParamTexture;
    }

protected:
    // allocate buffers from patchTables
    bool allocate(Far::PatchTables const *farPatchTables);

    PatchArrayVector _patchArrays;
    GLuint _indexBuffer;
    GLuint _patchParamTexture;
};


}  // end namespace Osd

}  // end namespace OPENSUBDIV_VERSION
using namespace OPENSUBDIV_VERSION;

}  // end namespace OpenSubdiv

#endif  // OPENSUBDIV3_OSD_GL_PATCH_TABLE_H