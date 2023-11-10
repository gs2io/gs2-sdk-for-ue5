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

    class GS2VERSION_API FCheckerDomain:
        public TSharedFromThis<FCheckerDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Version::Domain::FGs2VersionDomainPtr Service;
        const Gs2::Version::FGs2VersionRestClientPtr Client;

        public:
        TOptional<FString> ProjectToken;
        TSharedPtr<TArray<TSharedPtr<Gs2::Version::Model::FStatus>>> Warnings;
        TSharedPtr<TArray<TSharedPtr<Gs2::Version::Model::FStatus>>> Errors;
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> GetProjectToken() const
        {
            return ProjectToken;
        }
        TSharedPtr<TArray<TSharedPtr<Gs2::Version::Model::FStatus>>> GetWarnings() const
        {
            return Warnings;
        }
        TSharedPtr<TArray<TSharedPtr<Gs2::Version::Model::FStatus>>> GetErrors() const
        {
            return Errors;
        }
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FCheckerDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Version::Domain::FGs2VersionDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCheckerDomain(
            const FCheckerDomain& From
        );

        class GS2VERSION_API FCheckVersionTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FCheckerDomain>,
            public TSharedFromThis<FCheckVersionTask>
        {
            const TSharedPtr<FCheckerDomain> Self;
            const Request::FCheckVersionByUserIdRequestPtr Request;
        public:
            explicit FCheckVersionTask(
                const TSharedPtr<FCheckerDomain>& Self,
                const Request::FCheckVersionByUserIdRequestPtr Request
            );

            FCheckVersionTask(
                const FCheckVersionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FCheckerDomain>> Result
            ) override;
        };
        friend FCheckVersionTask;

        TSharedPtr<FAsyncTask<FCheckVersionTask>> CheckVersion(
            Request::FCheckVersionByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FCheckerDomain> FCheckerDomainPtr;
}
