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
 *
 * deny overwrite
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
#include "Distributor/Domain/Model/Expression.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Domain/Model/TransactionResult.h"
#include "Distributor/Domain/Model/TransactionResultAccessToken.h"

// Iterator
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"

// Notification
#include "Distributor/Model/AutoRunStampSheetNotification.h"
#include "Distributor/Model/AutoRunTransactionNotification.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Distributor::Domain
{
    DECLARE_EVENT_OneParam(FGs2DistributorDomain, FAutoRunStampSheetNotificationEvent, Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2DistributorDomain, FAutoRunTransactionNotificationEvent, Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr);

    class GS2DISTRIBUTOR_API FGs2DistributorDomain:
        public TSharedFromThis<FGs2DistributorDomain>
    {

        TSharedPtr<TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr>> CompletedStampSheets;
        TSharedPtr<FCriticalSection> CompletedStampSheetsMutex;
        TFunction<TOptional<FString>(const FString&, const TOptional<FString>&, const TOptional<FString>&, const TOptional<int32>&, const FString&, const FString&)> PutUserDataFunc;
        TFunction<bool(const FString&, const TOptional<int32>&, const FString&, const FString&)> SetListCachedFunc;
        TSharedPtr<TArray<Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr>> CompletedTransactions;
        TSharedPtr<FCriticalSection> CompletedTransactionsMutex;
        FAutoRunStampSheetNotificationEvent AutoRunStampSheetNotificationEvent;
        FAutoRunTransactionNotificationEvent AutoRunTransactionNotificationEvent;
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
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        class FCollectNamespacesTask;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateNamespaces(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2DISTRIBUTOR_API FSubscribeNamespacesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeNamespacesWithInitialCallTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2DistributorDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>> SubscribeNamespacesWithInitialCall(
            TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
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
            const FString Result,
            const TOptional<int32> TimeOffset = TOptional<int32>()
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result,
            const TOptional<int32> TimeOffset = TOptional<int32>()
        );

        TOptional<FString> PutUserData(
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<int32> TimeOffset,
            const FString Kind,
            const FString Payload
        );

        bool SetListCached(
            const TOptional<int32> TimeOffset,
            const FString Kind,
            const FString ParentKey
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
            const TOptional<int32> TimeOffset = TOptional<int32>()
        );
        FAutoRunStampSheetNotificationEvent& OnAutoRunStampSheetNotification();
        FAutoRunTransactionNotificationEvent& OnAutoRunTransactionNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        void SetUserDataStore(
            TFunction<TOptional<FString>(const FString&, const TOptional<FString>&, const TOptional<FString>&, const TOptional<int32>&, const FString&, const FString&)> Put,
            TFunction<bool(const FString&, const TOptional<int32>&, const FString&, const FString&)> SetListCached
        );

        TOptional<FString> PutUserData(
            const FString& Service,
            const TOptional<FString>& NamespaceName,
            const TOptional<FString>& UserId,
            const TOptional<int32>& TimeOffset,
            const FString& Kind,
            const FString& Payload
        ) const;
        bool SetListCached(
            const FString& Service,
            const TOptional<int32>& TimeOffset,
            const FString& Kind,
            const FString& ParentKey
        ) const;

        class FLoadUserDataTask final :
            public Gs2::Core::Util::TGs2Future<int32>,
            public TSharedFromThis<FLoadUserDataTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        public:
            GS2DISTRIBUTOR_API explicit FLoadUserDataTask(
                const TSharedPtr<FGs2DistributorDomain> Self,
                const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            );

            GS2DISTRIBUTOR_API virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<int32>> Result
            ) override;
        };
        friend FLoadUserDataTask;

        TSharedPtr<FAsyncTask<FLoadUserDataTask>> LoadUserData(
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        class GS2DISTRIBUTOR_API FDispatchTask final :
            public Gs2::Core::Util::TGs2Future<FGs2DistributorDomain>,
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
                TSharedPtr<TSharedPtr<FGs2DistributorDomain>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        class GS2DISTRIBUTOR_API FDispatchByUserIdTask final :
            public Gs2::Core::Util::TGs2Future<FGs2DistributorDomain>,
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
                TSharedPtr<TSharedPtr<FGs2DistributorDomain>> Result
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
