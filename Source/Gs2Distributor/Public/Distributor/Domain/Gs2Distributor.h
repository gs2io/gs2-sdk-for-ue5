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
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Distributor/Gs2Distributor.h"

// Model
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"

// Iterator
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"

// Notification
#include "Distributor/Model/AutoRunStampSheetNotification.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Distributor::Domain
{
    DECLARE_EVENT_OneParam(FGs2DistributorDomain, FAutoRunStampSheetNotificationEvent, Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr);

    class GS2DISTRIBUTOR_API FGs2DistributorDomain:
        public TSharedFromThis<FGs2DistributorDomain>
    {

        TSharedPtr<TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr>> CompletedStampSheets;
        TSharedPtr<FCriticalSection> CompletedStampSheetsMutex;
        FAutoRunStampSheetNotificationEvent AutoRunStampSheetNotificationEvent;
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2DistributorDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2DistributorDomain(
            const FGs2DistributorDomain& From
        );

        class GS2DISTRIBUTOR_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2DistributorDomain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Distributor::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        );

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
        FAutoRunStampSheetNotificationEvent& OnAutoRunStampSheetNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        class GS2DISTRIBUTOR_API FDispatchTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FDispatchTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        public:
            explicit FDispatchTask(
                const TSharedPtr<FGs2DistributorDomain> Self,
                const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        class GS2DISTRIBUTOR_API FDispatchByUserIdTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FDispatchByUserIdTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const FString UserId;
        public:
            explicit FDispatchByUserIdTask(
                const TSharedPtr<FGs2DistributorDomain> Self,
                const FString UserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FDispatchByUserIdTask;

        TSharedPtr<FAsyncTask<FDispatchByUserIdTask>> DispatchByUserId(
            const FString UserId
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2DistributorDomain> FGs2DistributorDomainPtr;
}
