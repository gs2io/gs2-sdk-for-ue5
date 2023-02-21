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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Auth/Domain/Gs2Auth.h"
#include "Auth/Domain/Model/AccessToken.h"

namespace Gs2::Auth::Domain
{

    FGs2AuthDomain::FGs2AuthDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Auth::FGs2AuthRestClient>(Session)),
        ParentKey("auth")
    {
    }

    FGs2AuthDomain::FGs2AuthDomain(
        const FGs2AuthDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain> FGs2AuthDomain::AccessToken(
    ) const
    {
        return MakeShared<Gs2::Auth::Domain::Model::FAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session
        );
    }

    void FGs2AuthDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2AuthDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2AuthDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2AuthDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

