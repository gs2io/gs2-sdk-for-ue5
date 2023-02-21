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

    class GS2VERSION_API FCheckerAccessTokenDomain:
        public TSharedFromThis<FCheckerAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Version::FGs2VersionRestClientPtr Client;

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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FCheckerAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCheckerAccessTokenDomain(
            const FCheckerAccessTokenDomain& From
        );

        class GS2VERSION_API FCheckVersionTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FCheckerAccessTokenDomain>,
            public TSharedFromThis<FCheckVersionTask>
        {
            const TSharedPtr<FCheckerAccessTokenDomain> Self;
            const Request::FCheckVersionRequestPtr Request;
        public:
            explicit FCheckVersionTask(
                const TSharedPtr<FCheckerAccessTokenDomain> Self,
                const Request::FCheckVersionRequestPtr Request
            );

            FCheckVersionTask(
                const FCheckVersionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FCheckerAccessTokenDomain>> Result
            ) override;
        };
        friend FCheckVersionTask;

        TSharedPtr<FAsyncTask<FCheckVersionTask>> CheckVersion(
            Request::FCheckVersionRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FCheckerAccessTokenDomain> FCheckerAccessTokenDomainPtr;
}
