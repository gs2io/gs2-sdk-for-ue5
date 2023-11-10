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

    class GS2DISTRIBUTOR_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Distributor::Domain::FGs2DistributorDomainPtr Service;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Result;
        TOptional<FString> ContextStack;
        TSharedPtr<TArray<FString>> TaskResults;
        TOptional<FString> SheetResult;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetResult() const
        {
            return Result;
        }
        TOptional<FString> GetContextStack() const
        {
            return ContextStack;
        }
        TSharedPtr<TArray<FString>> GetTaskResults() const
        {
            return TaskResults;
        }
        TOptional<FString> GetSheetResult() const
        {
            return SheetResult;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Distributor::Domain::FGs2DistributorDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2DISTRIBUTOR_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FCreateDistributorModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>,
            public TSharedFromThis<FCreateDistributorModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateDistributorModelMasterRequestPtr Request;
        public:
            explicit FCreateDistributorModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateDistributorModelMasterRequestPtr Request
            );

            FCreateDistributorModelMasterTask(
                const FCreateDistributorModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>> Result
            ) override;
        };
        friend FCreateDistributorModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateDistributorModelMasterTask>> CreateDistributorModelMaster(
            Request::FCreateDistributorModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain> CurrentDistributorMaster(
        );

        Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIteratorPtr DistributorModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDistributorModels(
            TFunction<void()> Callback
        );

        void UnsubscribeDistributorModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelDomain> DistributorModel(
            const FString DistributorName
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FDistributeDomain> Distribute(
        );

        Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelMastersIteratorPtr DistributorModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDistributorModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeDistributorModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain> DistributorModelMaster(
            const FString DistributorName
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2DISTRIBUTOR_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Distributor::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
