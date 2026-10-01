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

#include "Account/Gs2AccountErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Account/Error/PasswordIncorrectError.h"
#include "Account/Error/BannedInfinityError.h"
#include "Account/Error/TakeOverAlreadyExistsError.h"
#include "Account/Error/TakeOverIdentifierAlreadyUsedError.h"

namespace Gs2::Account
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Account"),
            &FGs2AccountErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2AccountErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("Authentication"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("account.password.invalid")))
            {
                Resolved = MakeShared<Gs2::Account::Error::FPasswordIncorrectError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("account.banned.infinity")))
            {
                Resolved = MakeShared<Gs2::Account::Error::FBannedInfinityError>(Source);
            }
        }
        else if (Method == TEXT("CreateTakeOver") || Method == TEXT("CreateTakeOverByUserId") || Method == TEXT("CreateTakeOverOpenIdConnect") || Method == TEXT("CreateTakeOverOpenIdConnectAndByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("account.takeOver.alreadyExists")))
            {
                Resolved = MakeShared<Gs2::Account::Error::FTakeOverAlreadyExistsError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("account.takeOver.userIdentifier.duplicate")))
            {
                Resolved = MakeShared<Gs2::Account::Error::FTakeOverIdentifierAlreadyUsedError>(Source);
            }
        }
        else if (Method == TEXT("UpdateTakeOver") || Method == TEXT("UpdateTakeOverByUserId") || Method == TEXT("DoTakeOver"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("account.password.invalid")))
            {
                Resolved = MakeShared<Gs2::Account::Error::FPasswordIncorrectError>(Source);
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