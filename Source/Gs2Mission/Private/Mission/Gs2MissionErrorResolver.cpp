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

#include "Mission/Gs2MissionErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Mission/Error/ConflictError.h"

namespace Gs2::Mission
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Mission"),
            &FGs2MissionErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2MissionErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("IncreaseCounterByUserId") || Method == TEXT("SetCounterByUserId") || Method == TEXT("DecreaseCounter") || Method == TEXT("DecreaseCounterByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("counter.increase.conflict")))
            {
                Resolved = MakeShared<Gs2::Mission::Error::FConflictError>(Source);
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