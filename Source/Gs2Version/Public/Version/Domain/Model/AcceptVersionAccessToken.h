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
    class FCurrentVersionMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2VERSION_API FAcceptVersionAccessTokenDomain:
        public TSharedFromThis<FAcceptVersionAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Version::FGs2VersionRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> VersionName;
    private:

        FString ParentKey;

    public:

        FAcceptVersionAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> VersionName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAcceptVersionAccessTokenDomain(
            const FAcceptVersionAccessTokenDomain& From
        );

        class GS2VERSION_API FAcceptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            const TSharedPtr<FAcceptVersionAccessTokenDomain> Self;
            const Request::FAcceptRequestPtr Request;
        public:
            explicit FAcceptTask(
                const TSharedPtr<FAcceptVersionAccessTokenDomain> Self,
                const Request::FAcceptRequestPtr Request
            );

            FAcceptTask(
                const FAcceptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomain>> Result
            ) override;
        };
        friend FAcceptTask;

        TSharedPtr<FAsyncTask<FAcceptTask>> Accept(
            Request::FAcceptRequestPtr Request
        );

        class GS2VERSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Model::FAcceptVersion>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FAcceptVersionAccessTokenDomain> Self;
            const Request::FGetAcceptVersionRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FAcceptVersionAccessTokenDomain> Self,
                const Request::FGetAcceptVersionRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Model::FAcceptVersion>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetAcceptVersionRequestPtr Request
        );

        class GS2VERSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FAcceptVersionAccessTokenDomain> Self;
            const Request::FDeleteAcceptVersionRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FAcceptVersionAccessTokenDomain> Self,
                const Request::FDeleteAcceptVersionRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteAcceptVersionRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> VersionName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> VersionName
        );

        class GS2VERSION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Model::FAcceptVersion>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FAcceptVersionAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAcceptVersionAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Model::FAcceptVersion>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FAcceptVersionAccessTokenDomain> FAcceptVersionAccessTokenDomainPtr;
}
