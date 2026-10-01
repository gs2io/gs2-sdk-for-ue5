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

#include "Chat/Gs2ChatErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Chat/Error/NoAccessPrivilegesError.h"
#include "Chat/Error/PasswordRequiredError.h"
#include "Chat/Error/PasswordIncorrectError.h"

namespace Gs2::Chat
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Chat"),
            &FGs2ChatErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2ChatErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("CreateRoom") || Method == TEXT("UpdateRoom") || Method == TEXT("DeleteRoom"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("room.allowUserIds.notInclude")))
            {
                Resolved = MakeShared<Gs2::Chat::Error::FNoAccessPrivilegesError>(Source);
            }
        }
        else if (Method == TEXT("DescribeMessages") || Method == TEXT("DescribeMessagesByUserId") || Method == TEXT("DescribeLatestMessages") || Method == TEXT("DescribeLatestMessagesByUserId") || Method == TEXT("Post") || Method == TEXT("PostByUserId") || Method == TEXT("GetMessage") || Method == TEXT("GetMessageByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("room.allowUserIds.notInclude")))
            {
                Resolved = MakeShared<Gs2::Chat::Error::FNoAccessPrivilegesError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("room.password.require")))
            {
                Resolved = MakeShared<Gs2::Chat::Error::FPasswordRequiredError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("room.password.invalid")))
            {
                Resolved = MakeShared<Gs2::Chat::Error::FPasswordIncorrectError>(Source);
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