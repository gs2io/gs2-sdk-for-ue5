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
#include "Guild/Gs2Guild.h"

// Model
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"

// Iterator
#include "Guild/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Guild/Domain/Iterator/DescribeGuildModelMastersIterator.h"
#include "Guild/Domain/Iterator/DescribeGuildModelsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsByUserIdIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsByUserIdIterator.h"
#include "Guild/Domain/Iterator/DescribeJoinedGuildsIterator.h"
#include "Guild/Domain/Iterator/DescribeJoinedGuildsByUserIdIterator.h"
#include "Guild/Domain/Iterator/DescribeReceiveRequestsIterator.h"
#include "Guild/Domain/Iterator/DescribeReceiveRequestsByGuildNameIterator.h"
#include "Guild/Domain/Iterator/DescribeSendRequestsIterator.h"
#include "Guild/Domain/Iterator/DescribeSendRequestsByUserIdIterator.h"
#include "Guild/Domain/Iterator/DescribeIgnoreUsersIterator.h"
#include "Guild/Domain/Iterator/DescribeIgnoreUsersByGuildNameIterator.h"

// Notification
#include "Guild/Model/ReceiveRequestNotification.h"
#include "Guild/Model/RemoveRequestNotification.h"
#include "Guild/Model/JoinNotification.h"
#include "Guild/Model/LeaveNotification.h"
#include "Guild/Model/ChangeMemberNotification.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Guild::Domain
{
    DECLARE_EVENT_OneParam(FGs2GuildDomain, FReceiveRequestNotificationEvent, Gs2::Guild::Model::FReceiveRequestNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2GuildDomain, FRemoveRequestNotificationEvent, Gs2::Guild::Model::FRemoveRequestNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2GuildDomain, FJoinNotificationEvent, Gs2::Guild::Model::FJoinNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2GuildDomain, FLeaveNotificationEvent, Gs2::Guild::Model::FLeaveNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2GuildDomain, FChangeMemberNotificationEvent, Gs2::Guild::Model::FChangeMemberNotificationPtr);

    class GS2GUILD_API FGs2GuildDomain:
        public TSharedFromThis<FGs2GuildDomain>
    {
        FReceiveRequestNotificationEvent ReceiveRequestNotificationEvent;
        FRemoveRequestNotificationEvent RemoveRequestNotificationEvent;
        FJoinNotificationEvent JoinNotificationEvent;
        FLeaveNotificationEvent LeaveNotificationEvent;
        FChangeMemberNotificationEvent ChangeMemberNotificationEvent;
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

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

        FGs2GuildDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2GuildDomain(
            const FGs2GuildDomain& From
        );

        class GS2GUILD_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        class GS2GUILD_API FDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GuildDomain>,
            public TSharedFromThis<FDumpUserDataTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FDumpUserDataTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FDumpUserDataByUserIdRequestPtr Request
            );

            FDumpUserDataTask(
                const FDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
            ) override;
        };
        friend FDumpUserDataTask;

        TSharedPtr<FAsyncTask<FDumpUserDataTask>> DumpUserData(
            Request::FDumpUserDataByUserIdRequestPtr Request
        );

        class GS2GUILD_API FCheckDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GuildDomain>,
            public TSharedFromThis<FCheckDumpUserDataTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckDumpUserDataTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FCheckDumpUserDataByUserIdRequestPtr Request
            );

            FCheckDumpUserDataTask(
                const FCheckDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
            ) override;
        };
        friend FCheckDumpUserDataTask;

        TSharedPtr<FAsyncTask<FCheckDumpUserDataTask>> CheckDumpUserData(
            Request::FCheckDumpUserDataByUserIdRequestPtr Request
        );

        class GS2GUILD_API FCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GuildDomain>,
            public TSharedFromThis<FCleanUserDataTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCleanUserDataTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FCleanUserDataByUserIdRequestPtr Request
            );

            FCleanUserDataTask(
                const FCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
            ) override;
        };
        friend FCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCleanUserDataTask>> CleanUserData(
            Request::FCleanUserDataByUserIdRequestPtr Request
        );

        class GS2GUILD_API FCheckCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GuildDomain>,
            public TSharedFromThis<FCheckCleanUserDataTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckCleanUserDataTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FCheckCleanUserDataByUserIdRequestPtr Request
            );

            FCheckCleanUserDataTask(
                const FCheckCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
            ) override;
        };
        friend FCheckCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCheckCleanUserDataTask>> CheckCleanUserData(
            Request::FCheckCleanUserDataByUserIdRequestPtr Request
        );

        class GS2GUILD_API FPrepareImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GuildDomain>,
            public TSharedFromThis<FPrepareImportUserDataTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FPrepareImportUserDataTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FPrepareImportUserDataByUserIdRequestPtr Request
            );

            FPrepareImportUserDataTask(
                const FPrepareImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
            ) override;
        };
        friend FPrepareImportUserDataTask;

        TSharedPtr<FAsyncTask<FPrepareImportUserDataTask>> PrepareImportUserData(
            Request::FPrepareImportUserDataByUserIdRequestPtr Request
        );

        class GS2GUILD_API FImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GuildDomain>,
            public TSharedFromThis<FImportUserDataTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FImportUserDataTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FImportUserDataByUserIdRequestPtr Request
            );

            FImportUserDataTask(
                const FImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
            ) override;
        };
        friend FImportUserDataTask;

        TSharedPtr<FAsyncTask<FImportUserDataTask>> ImportUserData(
            Request::FImportUserDataByUserIdRequestPtr Request
        );

        class GS2GUILD_API FCheckImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GuildDomain>,
            public TSharedFromThis<FCheckImportUserDataTask>
        {
            const TSharedPtr<FGs2GuildDomain> Self;
            const Request::FCheckImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckImportUserDataTask(
                const TSharedPtr<FGs2GuildDomain>& Self,
                const Request::FCheckImportUserDataByUserIdRequestPtr Request
            );

            FCheckImportUserDataTask(
                const FCheckImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
            ) override;
        };
        friend FCheckImportUserDataTask;

        TSharedPtr<FAsyncTask<FCheckImportUserDataTask>> CheckImportUserData(
            Request::FCheckImportUserDataByUserIdRequestPtr Request
        );

        Gs2::Guild::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Guild::Domain::Model::FNamespaceDomain> Namespace(
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
        FReceiveRequestNotificationEvent& OnReceiveRequestNotification();
        FRemoveRequestNotificationEvent& OnRemoveRequestNotification();
        FJoinNotificationEvent& OnJoinNotification();
        FLeaveNotificationEvent& OnLeaveNotification();
        FChangeMemberNotificationEvent& OnChangeMemberNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2GuildDomain> FGs2GuildDomainPtr;
}
