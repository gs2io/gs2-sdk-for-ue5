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
#include "Friend/Gs2Friend.h"

// Model
#include "Friend/Domain/Model/Namespace.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/Profile.h"
#include "Friend/Domain/Model/ProfileAccessToken.h"
#include "Friend/Domain/Model/Follow.h"
#include "Friend/Domain/Model/FollowAccessToken.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/FriendAccessToken.h"
#include "Friend/Domain/Model/BlackList.h"
#include "Friend/Domain/Model/BlackListAccessToken.h"
#include "Friend/Domain/Model/FollowUser.h"
#include "Friend/Domain/Model/FollowUserAccessToken.h"
#include "Friend/Domain/Model/FriendUser.h"
#include "Friend/Domain/Model/FriendUserAccessToken.h"
#include "Friend/Domain/Model/SendFriendRequest.h"
#include "Friend/Domain/Model/SendFriendRequestAccessToken.h"
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/ReceiveFriendRequestAccessToken.h"
#include "Friend/Domain/Model/PublicProfile.h"
#include "Friend/Domain/Model/PublicProfileAccessToken.h"
#include "Friend/Domain/Model/FriendRequest.h"
#include "Friend/Domain/Model/FriendRequestAccessToken.h"

// Iterator
#include "Friend/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Friend/Domain/Iterator/DescribeFriendsIterator.h"
#include "Friend/Domain/Iterator/DescribeFriendsByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeBlackListIterator.h"
#include "Friend/Domain/Iterator/DescribeBlackListByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeFollowsIterator.h"
#include "Friend/Domain/Iterator/DescribeFollowsByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeSendRequestsIterator.h"
#include "Friend/Domain/Iterator/DescribeSendRequestsByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeReceiveRequestsIterator.h"
#include "Friend/Domain/Iterator/DescribeReceiveRequestsByUserIdIterator.h"

// Notification
#include "Friend/Model/FollowNotification.h"
#include "Friend/Model/AcceptRequestNotification.h"
#include "Friend/Model/RejectRequestNotification.h"
#include "Friend/Model/DeleteFriendNotification.h"
#include "Friend/Model/ReceiveRequestNotification.h"
#include "Friend/Model/CancelRequestNotification.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Friend::Domain
{
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FFollowNotificationEvent, Gs2::Friend::Model::FFollowNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FAcceptRequestNotificationEvent, Gs2::Friend::Model::FAcceptRequestNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FRejectRequestNotificationEvent, Gs2::Friend::Model::FRejectRequestNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FDeleteFriendNotificationEvent, Gs2::Friend::Model::FDeleteFriendNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FReceiveRequestNotificationEvent, Gs2::Friend::Model::FReceiveRequestNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FCancelRequestNotificationEvent, Gs2::Friend::Model::FCancelRequestNotificationPtr);

    class GS2FRIEND_API FGs2FriendDomain:
        public TSharedFromThis<FGs2FriendDomain>
    {
        FFollowNotificationEvent FollowNotificationEvent;
        FAcceptRequestNotificationEvent AcceptRequestNotificationEvent;
        FRejectRequestNotificationEvent RejectRequestNotificationEvent;
        FDeleteFriendNotificationEvent DeleteFriendNotificationEvent;
        FReceiveRequestNotificationEvent ReceiveRequestNotificationEvent;
        FCancelRequestNotificationEvent CancelRequestNotificationEvent;
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
    private:

        FString ParentKey;

    public:

        FGs2FriendDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2FriendDomain(
            const FGs2FriendDomain& From
        );



        class GS2FRIEND_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );



        class GS2FRIEND_API FDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2FriendDomain>,
            public TSharedFromThis<FDumpUserDataTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FDumpUserDataTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FDumpUserDataByUserIdRequestPtr Request
            );

            FDumpUserDataTask(
                const FDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
            ) override;
        };
        friend FDumpUserDataTask;

        TSharedPtr<FAsyncTask<FDumpUserDataTask>> DumpUserData(
            Request::FDumpUserDataByUserIdRequestPtr Request
        );



        class GS2FRIEND_API FCheckDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2FriendDomain>,
            public TSharedFromThis<FCheckDumpUserDataTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckDumpUserDataTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FCheckDumpUserDataByUserIdRequestPtr Request
            );

            FCheckDumpUserDataTask(
                const FCheckDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
            ) override;
        };
        friend FCheckDumpUserDataTask;

        TSharedPtr<FAsyncTask<FCheckDumpUserDataTask>> CheckDumpUserData(
            Request::FCheckDumpUserDataByUserIdRequestPtr Request
        );



        class GS2FRIEND_API FCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2FriendDomain>,
            public TSharedFromThis<FCleanUserDataTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCleanUserDataTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FCleanUserDataByUserIdRequestPtr Request
            );

            FCleanUserDataTask(
                const FCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
            ) override;
        };
        friend FCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCleanUserDataTask>> CleanUserData(
            Request::FCleanUserDataByUserIdRequestPtr Request
        );



        class GS2FRIEND_API FCheckCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2FriendDomain>,
            public TSharedFromThis<FCheckCleanUserDataTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckCleanUserDataTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FCheckCleanUserDataByUserIdRequestPtr Request
            );

            FCheckCleanUserDataTask(
                const FCheckCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
            ) override;
        };
        friend FCheckCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCheckCleanUserDataTask>> CheckCleanUserData(
            Request::FCheckCleanUserDataByUserIdRequestPtr Request
        );



        class GS2FRIEND_API FPrepareImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2FriendDomain>,
            public TSharedFromThis<FPrepareImportUserDataTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FPrepareImportUserDataTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FPrepareImportUserDataByUserIdRequestPtr Request
            );

            FPrepareImportUserDataTask(
                const FPrepareImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
            ) override;
        };
        friend FPrepareImportUserDataTask;

        TSharedPtr<FAsyncTask<FPrepareImportUserDataTask>> PrepareImportUserData(
            Request::FPrepareImportUserDataByUserIdRequestPtr Request
        );



        class GS2FRIEND_API FImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2FriendDomain>,
            public TSharedFromThis<FImportUserDataTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FImportUserDataTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FImportUserDataByUserIdRequestPtr Request
            );

            FImportUserDataTask(
                const FImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
            ) override;
        };
        friend FImportUserDataTask;

        TSharedPtr<FAsyncTask<FImportUserDataTask>> ImportUserData(
            Request::FImportUserDataByUserIdRequestPtr Request
        );



        class GS2FRIEND_API FCheckImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2FriendDomain>,
            public TSharedFromThis<FCheckImportUserDataTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FCheckImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckImportUserDataTask(
                const TSharedPtr<FGs2FriendDomain>& Self,
                const Request::FCheckImportUserDataByUserIdRequestPtr Request
            );

            FCheckImportUserDataTask(
                const FCheckImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
            ) override;
        };
        friend FCheckImportUserDataTask;

        TSharedPtr<FAsyncTask<FCheckImportUserDataTask>> CheckImportUserData(
            Request::FCheckImportUserDataByUserIdRequestPtr Request
        );

        Gs2::Friend::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        class FCollectNamespacesTask;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateNamespaces(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2FRIEND_API FSubscribeNamespacesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeNamespacesWithInitialCallTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2FriendDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>> SubscribeNamespacesWithInitialCall(
            TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain> Namespace(
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

        // Gs2Distributor:DescribeUserData（ユーザーの全データの一括取得）の 1 エントリを、Kind に対応するモデルのキャッシュへ入れる。
        // 戻り値は親キー（未設定は知らない Kind ＝ SDK が古い / 対応表に無い / Payload が読めない）。呼び手は全ページを読み終えてから
        // SetListCached(TimeOffset, Kind, ParentKey) を呼ぶ。対応表は sdk-gen の type/user_data_cache.py（kind → モデル）。
        TOptional<FString> PutUserData(
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<int32> TimeOffset,
            const FString Kind,
            const FString Payload
        );

        // 一括取得で入れた Kind の親キーに「リストが揃った印」を立てる（Describe のイテレータがサーバーへ出なくなる）。
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
        FFollowNotificationEvent& OnFollowNotification();
        FAcceptRequestNotificationEvent& OnAcceptRequestNotification();
        FRejectRequestNotificationEvent& OnRejectRequestNotification();
        FDeleteFriendNotificationEvent& OnDeleteFriendNotification();
        FReceiveRequestNotificationEvent& OnReceiveRequestNotification();
        FCancelRequestNotificationEvent& OnCancelRequestNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2FriendDomain> FGs2FriendDomainPtr;
}
