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
 *
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Distributor::Domain
{
    class FGs2DistributorDomain;
    typedef TSharedPtr<FGs2DistributorDomain> FGs2DistributorDomainPtr;
}

namespace Gs2::Distributor::Domain::Model
{
    class FNamespaceDomain;
    class FDistributorModelMasterDomain;
    class FDistributorModelDomain;
    class FCurrentDistributorMasterDomain;
    class FDistributeDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStampSheetResultDomain;
    class FStampSheetResultAccessTokenDomain;

    class GS2DISTRIBUTOR_API FStampSheetResultDomain:
        public TSharedFromThis<FStampSheetResultDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Distributor::Domain::FGs2DistributorDomainPtr Service;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> TransactionId;
    private:

        FString ParentKey;

    public:

        FStampSheetResultDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Distributor::Domain::FGs2DistributorDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> TransactionId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStampSheetResultDomain(
            const FStampSheetResultDomain& From
        );

        class GS2DISTRIBUTOR_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FStampSheetResult>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStampSheetResultDomain> Self;
            const Request::FGetStampSheetResultByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStampSheetResultDomain>& Self,
                const Request::FGetStampSheetResultByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStampSheetResultByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> TransactionId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> TransactionId
        );

        class GS2DISTRIBUTOR_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FStampSheetResult>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStampSheetResultDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStampSheetResultDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        class GS2DISTRIBUTOR_API FModelNoCacheTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FStampSheetResult>,
            public TSharedFromThis<FModelNoCacheTask>
        {
            const TSharedPtr<FStampSheetResultDomain> Self;
        public:
            explicit FModelNoCacheTask(
                const TSharedPtr<FStampSheetResultDomain> Self
            );

            FModelNoCacheTask(
                const FModelNoCacheTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
            ) override;
        };
        friend FModelNoCacheTask;

        TSharedPtr<FAsyncTask<FModelNoCacheTask>> ModelNoCache();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Distributor::Model::FStampSheetResultPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStampSheetResultDomain> FStampSheetResultDomainPtr;
}
