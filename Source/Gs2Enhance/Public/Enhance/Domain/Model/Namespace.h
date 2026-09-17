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
#include "Enhance/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Enhance/Domain/Iterator/DescribeRateModelMastersIterator.h"
#include "Enhance/Domain/Iterator/DescribeUnleashRateModelsIterator.h"
#include "Enhance/Domain/Iterator/DescribeUnleashRateModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Enhance::Domain
{
    class FGs2EnhanceDomain;
    typedef TSharedPtr<FGs2EnhanceDomain> FGs2EnhanceDomainPtr;
}

namespace Gs2::Enhance::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FUnleashRateModelDomain;
    class FUnleashRateModelMasterDomain;
    class FEnhanceDomain;
    class FEnhanceAccessTokenDomain;
    class FProgressDomain;
    class FProgressAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2ENHANCE_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Enhance::Domain::FGs2EnhanceDomainPtr Service;
        const Gs2::Enhance::FGs2EnhanceRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
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
            const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );



        class GS2ENHANCE_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );



        class GS2ENHANCE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );



        class GS2ENHANCE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );



        class GS2ENHANCE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );



        class GS2ENHANCE_API FCreateUnleashRateModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>,
            public TSharedFromThis<FCreateUnleashRateModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateUnleashRateModelMasterRequestPtr Request;
        public:
            explicit FCreateUnleashRateModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateUnleashRateModelMasterRequestPtr Request
            );

            FCreateUnleashRateModelMasterTask(
                const FCreateUnleashRateModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>> Result
            ) override;
        };
        friend FCreateUnleashRateModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateUnleashRateModelMasterTask>> CreateUnleashRateModelMaster(
            Request::FCreateUnleashRateModelMasterRequestPtr Request
        );



        class GS2ENHANCE_API FCreateRateModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>,
            public TSharedFromThis<FCreateRateModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateRateModelMasterRequestPtr Request;
        public:
            explicit FCreateRateModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateRateModelMasterRequestPtr Request
            );

            FCreateRateModelMasterTask(
                const FCreateRateModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>> Result
            ) override;
        };
        friend FCreateRateModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateRateModelMasterTask>> CreateRateModelMaster(
            Request::FCreateRateModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Enhance::Domain::Model::FCurrentRateMasterDomain> CurrentRateMaster(
        );

        Gs2::Enhance::Domain::Iterator::FDescribeUnleashRateModelsIteratorPtr UnleashRateModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeUnleashRateModels(
            TFunction<void()> Callback

        );

        class FCollectUnleashRateModelsTask;

        Gs2::Core::Domain::CallbackID SubscribeUnleashRateModels(
            TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> Callback
        );

        void InvalidateUnleashRateModels();

        class GS2ENHANCE_API FSubscribeUnleashRateModelsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeUnleashRateModelsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> Callback;

        public:
            FSubscribeUnleashRateModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> Callback);
            FSubscribeUnleashRateModelsWithInitialCallTask(const FSubscribeUnleashRateModelsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeUnleashRateModelsWithInitialCallTask>> SubscribeUnleashRateModelsWithInitialCall(
            TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> Callback
        );
        void UnsubscribeUnleashRateModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelDomain> UnleashRateModel(
            const FString RateName
        );

        Gs2::Enhance::Domain::Iterator::FDescribeUnleashRateModelMastersIteratorPtr UnleashRateModelMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeUnleashRateModelMasters(
            TFunction<void()> Callback

        );

        class FCollectUnleashRateModelMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeUnleashRateModelMasters(
            TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateUnleashRateModelMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2ENHANCE_API FSubscribeUnleashRateModelMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeUnleashRateModelMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeUnleashRateModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeUnleashRateModelMastersWithInitialCallTask(const FSubscribeUnleashRateModelMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeUnleashRateModelMastersWithInitialCallTask>> SubscribeUnleashRateModelMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeUnleashRateModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain> UnleashRateModelMaster(
            const FString RateName
        );

        Gs2::Enhance::Domain::Iterator::FDescribeRateModelsIteratorPtr RateModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRateModels(
            TFunction<void()> Callback

        );

        class FCollectRateModelsTask;

        Gs2::Core::Domain::CallbackID SubscribeRateModels(
            TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> Callback
        );

        void InvalidateRateModels();

        class GS2ENHANCE_API FSubscribeRateModelsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeRateModelsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> Callback;

        public:
            FSubscribeRateModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> Callback);
            FSubscribeRateModelsWithInitialCallTask(const FSubscribeRateModelsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeRateModelsWithInitialCallTask>> SubscribeRateModelsWithInitialCall(
            TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> Callback
        );
        void UnsubscribeRateModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelDomain> RateModel(
            const FString RateName
        );

        TSharedPtr<Gs2::Enhance::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Enhance::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        Gs2::Enhance::Domain::Iterator::FDescribeRateModelMastersIteratorPtr RateModelMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRateModelMasters(
            TFunction<void()> Callback

        );

        class FCollectRateModelMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeRateModelMasters(
            TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateRateModelMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2ENHANCE_API FSubscribeRateModelMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeRateModelMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeRateModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeRateModelMastersWithInitialCallTask(const FSubscribeRateModelMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeRateModelMastersWithInitialCallTask>> SubscribeRateModelMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeRateModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain> RateModelMaster(
            const FString RateName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2ENHANCE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enhance::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        void Invalidate();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Enhance::Model::FNamespacePtr)> Callback
        );

        class GS2ENHANCE_API FSubscribeWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(Gs2::Enhance::Model::FNamespacePtr)> Callback;
        public:
            FSubscribeWithInitialCallTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                TFunction<void(Gs2::Enhance::Model::FNamespacePtr)> Callback
            );

            FSubscribeWithInitialCallTask(
                const FSubscribeWithInitialCallTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeWithInitialCallTask>> SubscribeWithInitialCall(
            TFunction<void(Gs2::Enhance::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
