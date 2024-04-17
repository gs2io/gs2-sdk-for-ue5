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
#include "Buff/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Buff/Domain/Iterator/DescribeBuffEntryModelsIterator.h"
#include "Buff/Domain/Iterator/DescribeBuffEntryModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Buff::Domain
{
    class FGs2BuffDomain;
    typedef TSharedPtr<FGs2BuffDomain> FGs2BuffDomainPtr;
}

namespace Gs2::Buff::Domain::Model
{
    class FNamespaceDomain;
    class FBuffEntryModelDomain;
    class FBuffEntryModelMasterDomain;
    class FBuffDomain;
    class FBuffAccessTokenDomain;
    class FCurrentBuffMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2BUFF_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Buff::Domain::FGs2BuffDomainPtr Service;
        const Gs2::Buff::FGs2BuffRestClientPtr Client;

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
            const Buff::Domain::FGs2BuffDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2BUFF_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2BUFF_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Buff::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2BUFF_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2BUFF_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2BUFF_API FCreateBuffEntryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Domain::Model::FBuffEntryModelMasterDomain>,
            public TSharedFromThis<FCreateBuffEntryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateBuffEntryModelMasterRequestPtr Request;
        public:
            explicit FCreateBuffEntryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateBuffEntryModelMasterRequestPtr Request
            );

            FCreateBuffEntryModelMasterTask(
                const FCreateBuffEntryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FBuffEntryModelMasterDomain>> Result
            ) override;
        };
        friend FCreateBuffEntryModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateBuffEntryModelMasterTask>> CreateBuffEntryModelMaster(
            Request::FCreateBuffEntryModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain> CurrentBuffMaster(
        );

        Gs2::Buff::Domain::Iterator::FDescribeBuffEntryModelMastersIteratorPtr BuffEntryModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBuffEntryModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeBuffEntryModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Buff::Domain::Model::FBuffEntryModelMasterDomain> BuffEntryModelMaster(
            const FString BuffEntryName
        );

        Gs2::Buff::Domain::Iterator::FDescribeBuffEntryModelsIteratorPtr BuffEntryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBuffEntryModels(
            TFunction<void()> Callback
        );

        void UnsubscribeBuffEntryModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Buff::Domain::Model::FBuffEntryModelDomain> BuffEntryModel(
            const FString BuffEntryName
        );

        TSharedPtr<Gs2::Buff::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Buff::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2BUFF_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Buff::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Buff::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Buff::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
