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
#include "Showcase/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemGroupMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesByUserIdIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Showcase::Domain
{
    class FGs2ShowcaseDomain;
    typedef TSharedPtr<FGs2ShowcaseDomain> FGs2ShowcaseDomainPtr;
}

namespace Gs2::Showcase::Domain::Model
{
    class FNamespaceDomain;
    class FSalesItemMasterDomain;
    class FSalesItemGroupMasterDomain;
    class FShowcaseMasterDomain;
    class FCurrentShowcaseMasterDomain;
    class FShowcaseDomain;
    class FShowcaseAccessTokenDomain;
    class FDisplayItemDomain;
    class FDisplayItemAccessTokenDomain;
    class FRandomShowcaseMasterDomain;
    class FRandomShowcaseDomain;
    class FRandomShowcaseAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FRandomShowcaseStatusDomain;
    class FRandomShowcaseStatusAccessTokenDomain;
    class FRandomDisplayItemDomain;
    class FRandomDisplayItemAccessTokenDomain;

    class GS2SHOWCASE_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Showcase::Domain::FGs2ShowcaseDomainPtr Service;
        const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

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
            const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );



        class GS2SHOWCASE_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );



        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );



        class GS2SHOWCASE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );



        class GS2SHOWCASE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );



        class GS2SHOWCASE_API FCreateSalesItemMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>,
            public TSharedFromThis<FCreateSalesItemMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateSalesItemMasterRequestPtr Request;
        public:
            explicit FCreateSalesItemMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateSalesItemMasterRequestPtr Request
            );

            FCreateSalesItemMasterTask(
                const FCreateSalesItemMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>> Result
            ) override;
        };
        friend FCreateSalesItemMasterTask;

        TSharedPtr<FAsyncTask<FCreateSalesItemMasterTask>> CreateSalesItemMaster(
            Request::FCreateSalesItemMasterRequestPtr Request
        );



        class GS2SHOWCASE_API FCreateSalesItemGroupMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain>,
            public TSharedFromThis<FCreateSalesItemGroupMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateSalesItemGroupMasterRequestPtr Request;
        public:
            explicit FCreateSalesItemGroupMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateSalesItemGroupMasterRequestPtr Request
            );

            FCreateSalesItemGroupMasterTask(
                const FCreateSalesItemGroupMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain>> Result
            ) override;
        };
        friend FCreateSalesItemGroupMasterTask;

        TSharedPtr<FAsyncTask<FCreateSalesItemGroupMasterTask>> CreateSalesItemGroupMaster(
            Request::FCreateSalesItemGroupMasterRequestPtr Request
        );



        class GS2SHOWCASE_API FCreateShowcaseMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain>,
            public TSharedFromThis<FCreateShowcaseMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateShowcaseMasterRequestPtr Request;
        public:
            explicit FCreateShowcaseMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateShowcaseMasterRequestPtr Request
            );

            FCreateShowcaseMasterTask(
                const FCreateShowcaseMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain>> Result
            ) override;
        };
        friend FCreateShowcaseMasterTask;

        TSharedPtr<FAsyncTask<FCreateShowcaseMasterTask>> CreateShowcaseMaster(
            Request::FCreateShowcaseMasterRequestPtr Request
        );



        class GS2SHOWCASE_API FCreateRandomShowcaseMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FRandomShowcaseMasterDomain>,
            public TSharedFromThis<FCreateRandomShowcaseMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateRandomShowcaseMasterRequestPtr Request;
        public:
            explicit FCreateRandomShowcaseMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateRandomShowcaseMasterRequestPtr Request
            );

            FCreateRandomShowcaseMasterTask(
                const FCreateRandomShowcaseMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseMasterDomain>> Result
            ) override;
        };
        friend FCreateRandomShowcaseMasterTask;

        TSharedPtr<FAsyncTask<FCreateRandomShowcaseMasterTask>> CreateRandomShowcaseMaster(
            Request::FCreateRandomShowcaseMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain> CurrentShowcaseMaster(
        );

        Gs2::Showcase::Domain::Iterator::FDescribeSalesItemMastersIteratorPtr SalesItemMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSalesItemMasters(
            TFunction<void()> Callback

        );

        class FCollectSalesItemMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeSalesItemMasters(
            TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateSalesItemMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2SHOWCASE_API FSubscribeSalesItemMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeSalesItemMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeSalesItemMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeSalesItemMastersWithInitialCallTask(const FSubscribeSalesItemMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeSalesItemMastersWithInitialCallTask>> SubscribeSalesItemMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeSalesItemMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain> SalesItemMaster(
            const FString SalesItemName
        );

        Gs2::Showcase::Domain::Iterator::FDescribeSalesItemGroupMastersIteratorPtr SalesItemGroupMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSalesItemGroupMasters(
            TFunction<void()> Callback

        );

        class FCollectSalesItemGroupMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeSalesItemGroupMasters(
            TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemGroupMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateSalesItemGroupMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2SHOWCASE_API FSubscribeSalesItemGroupMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeSalesItemGroupMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemGroupMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeSalesItemGroupMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemGroupMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeSalesItemGroupMastersWithInitialCallTask(const FSubscribeSalesItemGroupMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeSalesItemGroupMastersWithInitialCallTask>> SubscribeSalesItemGroupMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Showcase::Model::FSalesItemGroupMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeSalesItemGroupMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain> SalesItemGroupMaster(
            const FString SalesItemGroupName
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        Gs2::Showcase::Domain::Iterator::FDescribeShowcaseMastersIteratorPtr ShowcaseMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeShowcaseMasters(
            TFunction<void()> Callback

        );

        class FCollectShowcaseMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeShowcaseMasters(
            TFunction<void(TArray<Gs2::Showcase::Model::FShowcaseMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateShowcaseMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2SHOWCASE_API FSubscribeShowcaseMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeShowcaseMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Showcase::Model::FShowcaseMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeShowcaseMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FShowcaseMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeShowcaseMastersWithInitialCallTask(const FSubscribeShowcaseMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeShowcaseMastersWithInitialCallTask>> SubscribeShowcaseMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Showcase::Model::FShowcaseMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeShowcaseMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain> ShowcaseMaster(
            const FString ShowcaseName
        );

        Gs2::Showcase::Domain::Iterator::FDescribeRandomShowcaseMastersIteratorPtr RandomShowcaseMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRandomShowcaseMasters(
            TFunction<void()> Callback

        );

        class FCollectRandomShowcaseMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeRandomShowcaseMasters(
            TFunction<void(TArray<Gs2::Showcase::Model::FRandomShowcaseMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateRandomShowcaseMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2SHOWCASE_API FSubscribeRandomShowcaseMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeRandomShowcaseMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Showcase::Model::FRandomShowcaseMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeRandomShowcaseMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Showcase::Model::FRandomShowcaseMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeRandomShowcaseMastersWithInitialCallTask(const FSubscribeRandomShowcaseMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeRandomShowcaseMastersWithInitialCallTask>> SubscribeRandomShowcaseMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Showcase::Model::FRandomShowcaseMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeRandomShowcaseMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseMasterDomain> RandomShowcaseMaster(
            const FString ShowcaseName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        void Invalidate();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Showcase::Model::FNamespacePtr)> Callback
        );

        class GS2SHOWCASE_API FSubscribeWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(Gs2::Showcase::Model::FNamespacePtr)> Callback;
        public:
            FSubscribeWithInitialCallTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                TFunction<void(Gs2::Showcase::Model::FNamespacePtr)> Callback
            );

            FSubscribeWithInitialCallTask(
                const FSubscribeWithInitialCallTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeWithInitialCallTask>> SubscribeWithInitialCall(
            TFunction<void(Gs2::Showcase::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
