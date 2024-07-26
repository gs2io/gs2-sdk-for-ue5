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
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Model/Gs2DistributorEzConfig.h"
#include "Distributor/Model/Gs2DistributorEzDistributorModel.h"
#include "Distributor/Model/Gs2DistributorEzDistributeResource.h"
#include "Distributor/Model/Gs2DistributorEzStampSheetResult.h"
#include "Distributor/Model/Gs2DistributorEzAcquireAction.h"
#include "Distributor/Model/Gs2DistributorEzConsumeAction.h"
#include "Distributor/Model/Gs2DistributorEzVerifyAction.h"
#include "Gs2DistributorEzDistributorModelDomain.h"
#include "Distributor/Domain/Iterator/Gs2DistributorEzDescribeDistributorModelsIterator.h"
#include "Gs2DistributorEzUserDomain.h"
#include "Gs2DistributorEzUserDomain.h"
#include "Gs2DistributorEzUserGameSessionDomain.h"
#include "Gs2DistributorEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Distributor::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Result() const;
        TOptional<FString> ContextStack() const;
        TOptional<int32> StatusCode() const;
        TSharedPtr<TArray<int32>> VerifyTaskResultCodes() const;
        TSharedPtr<TArray<FString>> VerifyTaskResults() const;
        TSharedPtr<TArray<int32>> TaskResultCodes() const;
        TSharedPtr<TArray<FString>> TaskResults() const;
        TOptional<int32> SheetResultCode() const;
        TOptional<FString> SheetResult() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Distributor::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Distributor::Domain::Iterator::FEzDescribeDistributorModelsIteratorPtr DistributorModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDistributorModels(TFunction<void()> Callback);

        void UnsubscribeDistributorModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Distributor::Domain::Model::FEzDistributorModelDomainPtr DistributorModel(
            const FString DistributorName
        ) const;

        Gs2::UE5::Distributor::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Distributor::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
