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
}

namespace Gs2::Core::Domain::Model
{
    class GS2CORE_API FIssueTransactionEvent
    {
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>> ConsumeActions;
        const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>> AcquireActions;
        const TBigInt<1024, false> Rate;
        
    public:
        FIssueTransactionEvent(
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
            const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireActions,
            const TBigInt<1024, false>& Rate
        );

        FIssueTransactionEvent(
            const FIssueTransactionEvent& From
        );

        Gs2::Auth::Model::FAccessTokenPtr GetAccessToken() const;
        TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>> GetConsumeActions() const;
        TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>> GetAcquireActions() const;
        TBigInt<1024, false> GetRate() const;
    };
    typedef TSharedPtr<FIssueTransactionEvent> FIssueTransactionEventPtr;
}
