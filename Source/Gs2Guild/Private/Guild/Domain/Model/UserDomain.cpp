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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Auth/Domain/Gs2Auth.h"
#include "Guild/Domain/Model/User.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FCreateGuildTask::FCreateGuildTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FCreateGuildByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateGuildTask::FCreateGuildTask(
        const FCreateGuildTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CreateGuildByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FGuildDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetGuildModelName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCreateGuildTask>> FUserDomain::CreateGuild(
        Request::FCreateGuildByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGuildTask>>(this->AsShared(), Request);
    }

    FUserDomain::FAssumeTask::FAssumeTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FAssumeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FAssumeTask::FAssumeTask(
        const FAssumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FAssumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AssumeByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self->Gs2->Auth->AccessToken();
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetToken().IsSet())
            {
                Domain->Token = ResultModel->GetToken();
            }
            if (ResultModel->GetUserId().IsSet())
            {
                Domain->UserId = ResultModel->GetUserId();
            }
            if (ResultModel->GetExpire().IsSet())
            {
                Domain->Expire = ResultModel->GetExpire();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FAssumeTask>> FUserDomain::Assume(
        Request::FAssumeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAssumeTask>>(this->AsShared(), Request);
    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FSendRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendRequestByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetSendMemberRequest() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "SendMemberRequest::" + *RequestModel->GetGuildModelName()
                );
                const auto Key = Gs2::Guild::Domain::Model::FSendMemberRequestDomain::CreateCacheKey(
                    RequestModel->GetTargetGuildName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FSendMemberRequest::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetSendMemberRequest(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FGuildDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendRequestTask>> FUserDomain::SendRequest(
        Request::FSendRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FDeleteRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteRequestByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "SendMemberRequest::" + *RequestModel->GetGuildModelName()
                );
                const auto Key = Gs2::Guild::Domain::Model::FSendMemberRequestDomain::CreateCacheKey(
                    RequestModel->GetTargetGuildName()
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FSendMemberRequest::TypeName, ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            Request->GetGuildModelName(),
            Request->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDeleteTask>> FUserDomain::Delete(
        Request::FDeleteRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Guild::Domain::Iterator::FDescribeSendRequestsByUserIdIteratorPtr FUserDomain::SendRequests(
        const FString GuildModelName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeSendRequestsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            GuildModelName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSendRequests(
        const FString GuildModelName,
        TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FSendMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                    "SendMemberRequest::" + GuildModelName
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeSendRequests(
        const FString GuildModelName,
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FSendMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                    "SendMemberRequest::" + GuildModelName
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestDomain> FUserDomain::SendMemberRequest(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    Gs2::Guild::Domain::Iterator::FSearchGuildsByUserIdIteratorPtr FUserDomain::SearchGuilds(
        const FString GuildModelName,
        const TOptional<FString> DisplayName,
        const TSharedPtr<TArray<int32>> Attributes1,
        const TSharedPtr<TArray<int32>> Attributes2,
        const TSharedPtr<TArray<int32>> Attributes3,
        const TSharedPtr<TArray<int32>> Attributes4,
        const TSharedPtr<TArray<int32>> Attributes5,
        const TSharedPtr<TArray<FString>> JoinPolicies,
        const TOptional<bool> IncludeFullMembersGuild,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FSearchGuildsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            UserId,
            DisplayName,
            Attributes1,
            Attributes2,
            Attributes3,
            Attributes4,
            Attributes5,
            JoinPolicies,
            IncludeFullMembersGuild,
            TimeOffsetToken
        );
    }

    Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsByUserIdIteratorPtr FUserDomain::JoinedGuilds(
        const TOptional<FString> GuildModelName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            GuildModelName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeJoinedGuilds(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "JoinedGuild"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeJoinedGuilds(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "JoinedGuild"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FJoinedGuildDomain> FUserDomain::JoinedGuild(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FJoinedGuildDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

