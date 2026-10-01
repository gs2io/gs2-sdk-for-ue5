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

#include "Money/Gs2MoneyErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Money/Error/ConflictError.h"
#include "Money/Error/InsufficientError.h"
#include "Money/Error/ReceiptInvalidError.h"

namespace Gs2::Money
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Money"),
            &FGs2MoneyErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2MoneyErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("DepositByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("wallet.operation.conflict")))
            {
                Resolved = MakeShared<Gs2::Money::Error::FConflictError>(Source);
            }
        }
        else if (Method == TEXT("Withdraw") || Method == TEXT("WithdrawByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("wallet.operation.conflict")))
            {
                Resolved = MakeShared<Gs2::Money::Error::FConflictError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("wallet.balance.insufficient")))
            {
                Resolved = MakeShared<Gs2::Money::Error::FInsufficientError>(Source);
            }
        }
        else if (Method == TEXT("RecordReceipt"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("receipt.payload.invalid")))
            {
                Resolved = MakeShared<Gs2::Money::Error::FReceiptInvalidError>(Source);
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