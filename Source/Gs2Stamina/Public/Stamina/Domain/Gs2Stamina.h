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
#include "Stamina/Gs2Stamina.h"

// Model
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

// Iterator
#include "Stamina/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeMaxStaminaTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverIntervalTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverValueTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelsIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasByUserIdIterator.h"

// Notification

namespace Gs2::Stamina::Domain
{

    class GS2STAMINA_API FGs2StaminaDomain:
        public TSharedFromThis<FGs2StaminaDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Stamina::FGs2StaminaRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2StaminaDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2StaminaDomain(
            const FGs2StaminaDomain& From
        );

        class GS2STAMINA_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2StaminaDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2StaminaDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Stamina::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
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
    typedef TSharedPtr<FGs2StaminaDomain> FGs2StaminaDomainPtr;
}
