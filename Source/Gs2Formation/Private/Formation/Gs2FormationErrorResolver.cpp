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

#include "Formation/Gs2FormationErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Formation/Error/PropertyIdNotMatchRegexError.h"

namespace Gs2::Formation
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Formation"),
            &FGs2FormationErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2FormationErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("SetForm") || Method == TEXT("SetFormByUserId") || Method == TEXT("SetFormWithSignature") || Method == TEXT("SetPropertyForm") || Method == TEXT("SetPropertyFormByUserId") || Method == TEXT("SetPropertyFormWithSignature"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("formation.slot.propertyId.notMatchRegex")))
            {
                Resolved = MakeShared<Gs2::Formation::Error::FPropertyIdNotMatchRegexError>(Source);
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