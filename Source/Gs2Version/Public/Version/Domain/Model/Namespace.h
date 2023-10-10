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
#include "Version/Gs2Version.h"
#include "Version/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Version/Domain/Iterator/DescribeVersionModelMastersIterator.h"
#include "Version/Domain/Iterator/DescribeVersionModelsIterator.h"
#include "Version/Domain/Iterator/DescribeAcceptVersionsIterator.h"
#include "Version/Domain/Iterator/DescribeAcceptVersionsByUserIdIterator.h"

namespace Gs2::Version::Domain::Model
{
    class FNamespaceDomain;
    class FVersionModelMasterDomain;
    class FVersionModelDomain;
    class FAcceptVersionDomain;
    class FAcceptVersionAccessTokenDomain;
    class FCheckerDomain;
    class FCheckerAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FCurrentVersionMasterDomain;

    class GS2VERSION_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Version::FGs2VersionRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Url;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetUrl() const
        {
            return Url;
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
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2VERSION_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2VERSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Version::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2VERSION_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2VERSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2VERSION_API FCreateVersionModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FVersionModelMasterDomain>,
            public TSharedFromThis<FCreateVersionModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateVersionModelMasterRequestPtr Request;
        public:
            explicit FCreateVersionModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateVersionModelMasterRequestPtr Request
            );

            FCreateVersionModelMasterTask(
                const FCreateVersionModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FVersionModelMasterDomain>> Result
            ) override;
        };
        friend FCreateVersionModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateVersionModelMasterTask>> CreateVersionModelMaster(
            Request::FCreateVersionModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Version::Domain::Model::FCurrentVersionMasterDomain> CurrentVersionMaster(
        ) const;

        Gs2::Version::Domain::Iterator::FDescribeVersionModelsIteratorPtr VersionModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeVersionModels(
            TFunction<void()> Callback
        );

        void UnsubscribeVersionModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Version::Domain::Model::FVersionModelDomain> VersionModel(
            const FString VersionName
        ) const;

        TSharedPtr<Gs2::Version::Domain::Model::FUserDomain> User(
            const FString UserId
        ) const;

        TSharedPtr<Gs2::Version::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        ) const;

        Gs2::Version::Domain::Iterator::FDescribeVersionModelMastersIteratorPtr VersionModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeVersionModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeVersionModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Version::Domain::Model::FVersionModelMasterDomain> VersionModelMaster(
            const FString VersionName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2VERSION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Version::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Version::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
