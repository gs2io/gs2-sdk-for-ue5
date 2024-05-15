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

#include "Guild/Domain/Model/UserAccessToken.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FCreateGuildTask::FCreateGuildTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FCreateGuildRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FCreateGuildTask::FCreateGuildTask(
        const FCreateGuildTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FCreateGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->CreateGuild(
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

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FCreateGuildTask>> FUserAccessTokenDomain::CreateGuild(
        Request::FCreateGuildRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGuildTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FAssumeTask::FAssumeTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FAssumeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FAssumeTask::FAssumeTask(
        const FAssumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FAssumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->Assume(
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

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FAssumeTask>> FUserAccessTokenDomain::Assume(
        Request::FAssumeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAssumeTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FSendRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->SendRequest(
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
                    Self->UserId(),
                    "SendMemberRequest::" + *RequestModel->GetGuildModelName()
                );
                const auto Key = Gs2::Guild::Domain::Model::FSendMemberRequestDomain::CreateCacheKey(
                    ResultModel->GetSendMemberRequest()->GetTargetGuildName()
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
            RequestModel->GetGuildModelName(),
            RequestModel->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSendRequestTask>> FUserAccessTokenDomain::SendRequest(
        Request::FSendRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FDeleteRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->DeleteRequest(
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
                    Self->UserId(),
                    "SendMemberRequest::" + *RequestModel->GetGuildModelName()
                );
                const auto Key = Gs2::Guild::Domain::Model::FSendMemberRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTargetGuildName()
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FSendMemberRequest::TypeName, ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            Request->GetGuildModelName(),
            Request->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FDeleteTask>> FUserAccessTokenDomain::Delete(
        Request::FDeleteRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Guild::Domain::Iterator::FDescribeSendRequestsIteratorPtr FUserAccessTokenDomain::SendRequests(
        const FString GuildModelName
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeSendRequestsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            GuildModelName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSendRequests(
        const FString GuildModelName,
        TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FSendMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                    "SendMemberRequest::" + GuildModelName
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeSendRequests(
        const FString GuildModelName,
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FSendMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                    "SendMemberRequest::" + GuildModelName
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain> FUserAccessTokenDomain::SendMemberRequest(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    Gs2::Guild::Domain::Iterator::FSearchGuildsIteratorPtr FUserAccessTokenDomain::SearchGuilds(
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
        return MakeShared<Gs2::Guild::Domain::Iterator::FSearchGuildsIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            AccessToken,
            DisplayName,
            Attributes1,
            Attributes2,
            Attributes3,
            Attributes4,
            Attributes5,
            JoinPolicies,
            IncludeFullMembersGuild
        );
    }

    Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIteratorPtr FUserAccessTokenDomain::JoinedGuilds(
        const TOptional<FString> GuildModelName
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            GuildModelName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeJoinedGuilds(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "JoinedGuild"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeJoinedGuilds(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "JoinedGuild"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomain> FUserAccessTokenDomain::JoinedGuild(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
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

    FString FUserAccessTokenDomain::CreateCacheKey(
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

