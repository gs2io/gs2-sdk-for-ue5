/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Datastore/Gs2DatastoreErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Datastore/Error/InvalidStatusError.h"
#include "Datastore/Error/NotUploadedError.h"

namespace Gs2::Datastore
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Datastore"),
            &FGs2DatastoreErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2DatastoreErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("DoneUpload") || Method == TEXT("DoneUploadByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("dataObject.status.invalid")))
            {
                Resolved = MakeShared<Gs2::Datastore::Error::FInvalidStatusError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("dataObject.file.notUploaded")))
            {
                Resolved = MakeShared<Gs2::Datastore::Error::FNotUploadedError>(Source);
            }
        }
        else if (Method == TEXT("DeleteDataObject") || Method == TEXT("DeleteDataObjectByUserId") || Method == TEXT("RestoreDataObject"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("dataObject.status.invalid")))
            {
                Resolved = MakeShared<Gs2::Datastore::Error::FInvalidStatusError>(Source);
            }
        }
        if (!Resolved.IsValid())
        {
            return Source;
        }
        Resolved->SetMetadata(Source->GetMetadata());
        return Resolved;
    }
}