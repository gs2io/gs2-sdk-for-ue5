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

#include "Money2/Gs2Money2ErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Money2/Error/ConflictError.h"
#include "Money2/Error/InsufficientError.h"
#include "Money2/Error/ReceiptInvalidError.h"
#include "Money2/Error/AlreadyUsedError.h"
#include "Money2/Error/LockPeriodNotElapsedError.h"

namespace Gs2::Money2
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Money2"),
            &FGs2Money2ErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2Money2ErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
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
                Resolved = MakeShared<Gs2::Money2::Error::FConflictError>(Source);
            }
        }
        else if (Method == TEXT("Withdraw") || Method == TEXT("WithdrawByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("wallet.operation.conflict")))
            {
                Resolved = MakeShared<Gs2::Money2::Error::FConflictError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("wallet.balance.insufficient")))
            {
                Resolved = MakeShared<Gs2::Money2::Error::FInsufficientError>(Source);
            }
        }
        else if (Method == TEXT("VerifyReceipt") || Method == TEXT("VerifyReceiptByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("receipt.payload.invalid")))
            {
                Resolved = MakeShared<Gs2::Money2::Error::FReceiptInvalidError>(Source);
            }
        }
        else if (Method == TEXT("AllocateSubscriptionStatus") || Method == TEXT("AllocateSubscriptionStatusByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("subscription.transaction.used")))
            {
                Resolved = MakeShared<Gs2::Money2::Error::FAlreadyUsedError>(Source);
            }
        }
        else if (Method == TEXT("TakeoverSubscriptionStatus") || Method == TEXT("TakeoverSubscriptionStatusByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("subscription.transaction.used")))
            {
                Resolved = MakeShared<Gs2::Money2::Error::FLockPeriodNotElapsedError>(Source);
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