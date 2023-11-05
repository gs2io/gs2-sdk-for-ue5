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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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

    class GS2VERSION_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Version::FGs2VersionRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2VERSION_API FCalculateSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Version::Domain::Model::FUserDomain>,
            public TSharedFromThis<FCalculateSignatureTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FCalculateSignatureRequestPtr Request;
        public:
            explicit FCalculateSignatureTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FCalculateSignatureRequestPtr Request
            );

            FCalculateSignatureTask(
                const FCalculateSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FCalculateSignatureTask;

        TSharedPtr<FAsyncTask<FCalculateSignatureTask>> CalculateSignature(
            Request::FCalculateSignatureRequestPtr Request
        );

        Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsByUserIdIteratorPtr AcceptVersions(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAcceptVersions(
            TFunction<void()> Callback
        );

        void UnsubscribeAcceptVersions(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionDomain> AcceptVersion(
            const FString VersionName
        ) const;

        TSharedPtr<Gs2::Version::Domain::Model::FCheckerDomain> Checker(
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
