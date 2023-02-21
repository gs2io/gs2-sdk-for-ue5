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

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Auth/Gs2Auth.h"

// Model
#include "Auth/Domain/Model/AccessToken.h"

// Iterator

// Notification

namespace Gs2::Auth::Domain
{

    class GS2AUTH_API FGs2AuthDomain:
        public TSharedFromThis<FGs2AuthDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Auth::FGs2AuthRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2AuthDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2AuthDomain(
            const FGs2AuthDomain& From
        );

        TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain> AccessToken(
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2AuthDomain> FGs2AuthDomainPtr;
}
