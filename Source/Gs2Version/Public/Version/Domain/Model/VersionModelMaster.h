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

    class GS2VERSION_API FVersionModelMasterDomain:
        public TSharedFromThis<FVersionModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Version::FGs2VersionRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> VersionName;
    private:

        FString ParentKey;

    public:

        FVersionModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> VersionName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FVersionModelMasterDomain(
            const FVersionModelMasterDomain& From
        );

        class GS2VERSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Model::FVersionModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FVersionModelMasterDomain> Self;
            const Request::FGetVersionModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FVersionModelMasterDomain> Self,
                const Request::FGetVersionModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetVersionModelMasterRequestPtr Request
        );

        class GS2VERSION_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FVersionModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FVersionModelMasterDomain> Self;
            const Request::FUpdateVersionModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FVersionModelMasterDomain> Self,
                const Request::FUpdateVersionModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FVersionModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateVersionModelMasterRequestPtr Request
        );

        class GS2VERSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FVersionModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FVersionModelMasterDomain> Self;
            const Request::FDeleteVersionModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FVersionModelMasterDomain> Self,
                const Request::FDeleteVersionModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FVersionModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteVersionModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> VersionName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> VersionName
        );

        class GS2VERSION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Model::FVersionModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FVersionModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FVersionModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FVersionModelMasterDomain> FVersionModelMasterDomainPtr;
}
