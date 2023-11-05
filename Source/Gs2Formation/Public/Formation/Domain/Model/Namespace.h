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
#include "Formation/Gs2Formation.h"
#include "Formation/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Formation/Domain/Iterator/DescribeFormModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormModelsIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Formation::Domain::Model
{
    class FNamespaceDomain;
    class FFormModelDomain;
    class FFormModelMasterDomain;
    class FMoldModelDomain;
    class FMoldModelMasterDomain;
    class FPropertyFormModelDomain;
    class FPropertyFormModelMasterDomain;
    class FCurrentFormMasterDomain;
    class FMoldDomain;
    class FMoldAccessTokenDomain;
    class FFormDomain;
    class FFormAccessTokenDomain;
    class FPropertyFormDomain;
    class FPropertyFormAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2FORMATION_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Formation::FGs2FormationRestClientPtr Client;

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
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2FORMATION_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2FORMATION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2FORMATION_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2FORMATION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2FORMATION_API FCreatePropertyFormModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain>,
            public TSharedFromThis<FCreatePropertyFormModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreatePropertyFormModelMasterRequestPtr Request;
        public:
            explicit FCreatePropertyFormModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreatePropertyFormModelMasterRequestPtr Request
            );

            FCreatePropertyFormModelMasterTask(
                const FCreatePropertyFormModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain>> Result
            ) override;
        };
        friend FCreatePropertyFormModelMasterTask;

        TSharedPtr<FAsyncTask<FCreatePropertyFormModelMasterTask>> CreatePropertyFormModelMaster(
            Request::FCreatePropertyFormModelMasterRequestPtr Request
        );

        class GS2FORMATION_API FCreateFormModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FFormModelMasterDomain>,
            public TSharedFromThis<FCreateFormModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateFormModelMasterRequestPtr Request;
        public:
            explicit FCreateFormModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateFormModelMasterRequestPtr Request
            );

            FCreateFormModelMasterTask(
                const FCreateFormModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain>> Result
            ) override;
        };
        friend FCreateFormModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateFormModelMasterTask>> CreateFormModelMaster(
            Request::FCreateFormModelMasterRequestPtr Request
        );

        class GS2FORMATION_API FCreateMoldModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FMoldModelMasterDomain>,
            public TSharedFromThis<FCreateMoldModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateMoldModelMasterRequestPtr Request;
        public:
            explicit FCreateMoldModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateMoldModelMasterRequestPtr Request
            );

            FCreateMoldModelMasterTask(
                const FCreateMoldModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelMasterDomain>> Result
            ) override;
        };
        friend FCreateMoldModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateMoldModelMasterTask>> CreateMoldModelMaster(
            Request::FCreateMoldModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain> CurrentFormMaster(
        ) const;

        Gs2::Formation::Domain::Iterator::FDescribeMoldModelsIteratorPtr MoldModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMoldModels(
            TFunction<void()> Callback
        );

        void UnsubscribeMoldModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelDomain> MoldModel(
            const FString MoldModelName
        ) const;

        Gs2::Formation::Domain::Iterator::FDescribePropertyFormModelsIteratorPtr PropertyFormModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePropertyFormModels(
            TFunction<void()> Callback
        );

        void UnsubscribePropertyFormModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormModelDomain> PropertyFormModel(
            const FString PropertyFormModelName
        ) const;

        TSharedPtr<Gs2::Formation::Domain::Model::FUserDomain> User(
            const FString UserId
        ) const;

        TSharedPtr<Gs2::Formation::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        ) const;

        Gs2::Formation::Domain::Iterator::FDescribePropertyFormModelMastersIteratorPtr PropertyFormModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePropertyFormModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribePropertyFormModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain> PropertyFormModelMaster(
            const FString PropertyFormModelName
        ) const;

        Gs2::Formation::Domain::Iterator::FDescribeFormModelMastersIteratorPtr FormModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeFormModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeFormModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain> FormModelMaster(
            const FString FormModelName
        ) const;

        Gs2::Formation::Domain::Iterator::FDescribeMoldModelMastersIteratorPtr MoldModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMoldModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeMoldModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelMasterDomain> MoldModelMaster(
            const FString MoldModelName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2FORMATION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Formation::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
