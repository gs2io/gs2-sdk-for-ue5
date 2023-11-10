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

#include "Core/Domain/Model/IssueTransactionEvent.h"

namespace Gs2::Core::Domain::Model
{
    FIssueTransactionEvent::FIssueTransactionEvent(
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
        const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireActions,
        const TBigInt<1024, false>& Rate
    ): AccessToken(AccessToken), ConsumeActions(ConsumeActions), AcquireActions(AcquireActions), Rate(Rate)
    {

    }

    FIssueTransactionEvent::FIssueTransactionEvent(
        const FIssueTransactionEvent& From
    ): AccessToken(From.AccessToken), ConsumeActions(From.ConsumeActions), AcquireActions(From.AcquireActions), Rate(From.Rate)
    {
            
    }

    Gs2::Auth::Model::FAccessTokenPtr FIssueTransactionEvent::GetAccessToken() const
    {
        return AccessToken;
    }

    TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>> FIssueTransactionEvent::GetConsumeActions() const
    {
        return ConsumeActions;
    }

    TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>> FIssueTransactionEvent::GetAcquireActions() const
    {
        return AcquireActions;
    }

    TBigInt<1024, false> FIssueTransactionEvent::GetRate() const
    {
        return Rate;
    }
}
