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
#include "News/Gs2News.h"
#include "News/Domain/Iterator/DescribeNamespacesIterator.h"
#include "News/Domain/Iterator/DescribeProgressesIterator.h"
#include "News/Domain/Iterator/DescribeOutputsIterator.h"
#include "News/Domain/Iterator/DescribeNewsIterator.h"
#include "News/Domain/Iterator/DescribeNewsByUserIdIterator.h"

namespace Gs2::News::Domain::Model
{
    class FNamespaceDomain;
    class FProgressDomain;
    class FOutputDomain;
    class FCurrentNewsMasterDomain;
    class FNewsDomain;
    class FNewsAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FSetCookieRequestEntryDomain;

    class GS2NEWS_API FCurrentNewsMasterDomain:
        public TSharedFromThis<FCurrentNewsMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::News::FGs2NewsRestClientPtr Client;

        public:
        TOptional<FString> UploadToken;
        TOptional<FString> TemplateUploadUrl;
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetTemplateUploadUrl() const
        {
            return TemplateUploadUrl;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentNewsMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentNewsMasterDomain(
            const FCurrentNewsMasterDomain& From
        );

        class GS2NEWS_API FPrepareUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>,
            public TSharedFromThis<FPrepareUpdateTask>
        {
            const TSharedPtr<FCurrentNewsMasterDomain> Self;
            const Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request;
        public:
            explicit FPrepareUpdateTask(
                const TSharedPtr<FCurrentNewsMasterDomain> Self,
                const Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request
            );

            FPrepareUpdateTask(
                const FPrepareUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>> Result
            ) override;
        };
        friend FPrepareUpdateTask;

        TSharedPtr<FAsyncTask<FPrepareUpdateTask>> PrepareUpdate(
            Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request
        );

        class GS2NEWS_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentNewsMasterDomain> Self;
            const Request::FUpdateCurrentNewsMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentNewsMasterDomain> Self,
                const Request::FUpdateCurrentNewsMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentNewsMasterRequestPtr Request
        );

        class GS2NEWS_API FPrepareUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>,
            public TSharedFromThis<FPrepareUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentNewsMasterDomain> Self;
            const Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request;
        public:
            explicit FPrepareUpdateFromGitHubTask(
                const TSharedPtr<FCurrentNewsMasterDomain> Self,
                const Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request
            );

            FPrepareUpdateFromGitHubTask(
                const FPrepareUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>> Result
            ) override;
        };
        friend FPrepareUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FPrepareUpdateFromGitHubTask>> PrepareUpdateFromGitHub(
            Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FCurrentNewsMasterDomain> FCurrentNewsMasterDomainPtr;
}
