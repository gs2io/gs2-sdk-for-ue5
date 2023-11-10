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
#include "Version/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Version/Domain/Iterator/DescribeVersionModelMastersIterator.h"
#include "Version/Domain/Iterator/DescribeVersionModelsIterator.h"
#include "Version/Domain/Iterator/DescribeAcceptVersionsIterator.h"
#include "Version/Domain/Iterator/DescribeAcceptVersionsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Version::Domain
{
    class FGs2VersionDomain;
    typedef TSharedPtr<FGs2VersionDomain> FGs2VersionDomainPtr;
}

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

    class GS2VERSION_API FAcceptVersionDomain:
        public TSharedFromThis<FAcceptVersionDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Version::Domain::FGs2VersionDomainPtr Service;
        const Gs2::Version::FGs2VersionRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> VersionName;
    private:

        FString ParentKey;

    public:

        FAcceptVersionDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Version::Domain::FGs2VersionDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> VersionName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAcceptVersionDomain(
            const FAcceptVersionDomain& From
        );

        class GS2VERSION_API FAcceptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FAcceptVersionDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            const TSharedPtr<FAcceptVersionDomain> Self;
            const Request::FAcceptByUserIdRequestPtr Request;
        public:
            explicit FAcceptTask(
                const TSharedPtr<FAcceptVersionDomain>& Self,
                const Request::FAcceptByUserIdRequestPtr Request
            );

            FAcceptTask(
                const FAcceptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionDomain>> Result
            ) override;
        };
        friend FAcceptTask;

        TSharedPtr<FAsyncTask<FAcceptTask>> Accept(
            Request::FAcceptByUserIdRequestPtr Request
        );

        class GS2VERSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Model::FAcceptVersion>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FAcceptVersionDomain> Self;
            const Request::FGetAcceptVersionByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FAcceptVersionDomain>& Self,
                const Request::FGetAcceptVersionByUserIdRequestPtr Request
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
            Request::FGetAcceptVersionByUserIdRequestPtr Request
        );

        class GS2VERSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FAcceptVersionDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FAcceptVersionDomain> Self;
            const Request::FDeleteAcceptVersionByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FAcceptVersionDomain>& Self,
                const Request::FDeleteAcceptVersionByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteAcceptVersionByUserIdRequestPtr Request
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
            const TSharedPtr<FAcceptVersionDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAcceptVersionDomain> Self
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

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Version::Model::FAcceptVersionPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FAcceptVersionDomain> FAcceptVersionDomainPtr;
}
