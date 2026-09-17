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

#pragma once

#include "CoreMinimal.h"
#include "Core/Model/Gs2Error.h"
#include "Math/BigInt.h"

namespace Gs2::Auth::Model
{
    class FAccessToken;
    typedef TSharedPtr<FAccessToken> FAccessTokenPtr;
}

namespace Gs2::Core::Model
{
    class FConsumeAction;
    typedef TSharedPtr<FConsumeAction> FConsumeActionPtr;

    class FAcquireAction;
    typedef TSharedPtr<FAcquireAction> FAcquireActionPtr;

    class FVerifyAction;
    typedef TSharedPtr<FVerifyAction> FVerifyActionPtr;
}

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    class FPreparedSpeculativeCommit;
}

namespace Gs2::Core::Domain::Model
{
    class GS2CORE_API FIssueTransactionEvent
    {
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>> ConsumeActions;
        const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>> AcquireActions;
        const TBigInt<1024, false> Rate;
        const Gs2::Core::Model::FVerifyActionPtr VerifyAction;
        const bool InverseVerify;
        Gs2::Core::Model::FGs2ErrorPtr Error;
        TSharedPtr<TFunction<void()>> Commit;
        TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit> PreparedCommit;
        
    public:
        FIssueTransactionEvent(
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
            const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireActions,
            const TBigInt<1024, false>& Rate
        );

        FIssueTransactionEvent(
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Core::Model::FVerifyActionPtr& VerifyAction,
            const TBigInt<1024, false>& Rate,
            bool InverseVerify
        );

        FIssueTransactionEvent(
            const FIssueTransactionEvent& From
        );

        Gs2::Auth::Model::FAccessTokenPtr GetAccessToken() const;
        TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>> GetConsumeActions() const;
        TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>> GetAcquireActions() const;
        TBigInt<1024, false> GetRate() const;
        Gs2::Core::Model::FVerifyActionPtr GetVerifyAction() const;
        bool IsInverseVerify() const;
        Gs2::Core::Model::FGs2ErrorPtr GetError() const;
        void SetError(const Gs2::Core::Model::FGs2ErrorPtr& Error);
        TSharedPtr<TFunction<void()>> GetCommit() const;
        void SetCommit(const TSharedPtr<TFunction<void()>>& Commit);
        TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit> GetPreparedCommit() const;
        void SetPreparedCommit(
            const TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>& PreparedCommit
        );
    };
    typedef TSharedPtr<FIssueTransactionEvent> FIssueTransactionEventPtr;
}
