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

#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/ReceivedAccessToken.h"
#include "Inbox/Domain/SpeculativeExecutor/Transaction/ReadMessageByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FMessageAccessTokenDomain::FMessageAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> MessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        MessageName(MessageName),
        ParentKey(Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Message"
        ))
    {
    }

    FMessageAccessTokenDomain::FMessageAccessTokenDomain(
        const FMessageAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        MessageName(From.MessageName),
        ParentKey(From.ParentKey)
    {

    }

    FMessageAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FMessageAccessTokenDomain>& Self,
        const Request::FGetMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FMessage>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->GetMessage(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FGetTask>> FMessageAccessTokenDomain::Get(
        Request::FGetMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMessageAccessTokenDomain::FOpenTask::FOpenTask(
        const TSharedPtr<FMessageAccessTokenDomain>& Self,
        const Request::FOpenMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageAccessTokenDomain::FOpenTask::FOpenTask(
        const FOpenTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FOpenTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->OpenMessage(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Inbox::Model::FMessage::TypeName, ParentKey, Key);
                Self->Gs2->Cache->ClearListCache(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FOpenTask>> FMessageAccessTokenDomain::Open(
        Request::FOpenMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FOpenTask>>(this->AsShared(), Request);
    }

    FMessageAccessTokenDomain::FReadTask::FReadTask(
        const TSharedPtr<FMessageAccessTokenDomain>& Self,
        const Request::FReadMessageRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FMessageAccessTokenDomain::FReadTask::FReadTask(
        const FReadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FReadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMessageName(Self->MessageName);

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FReadMessageByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FReadMessageByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->ReadMessage(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FReadTask>> FMessageAccessTokenDomain::Read(
        Request::FReadMessageRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReadTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FMessageAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMessageAccessTokenDomain>& Self,
        const Request::FDeleteMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->DeleteMessage(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Inbox::Model::FMessage::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FDeleteTask>> FMessageAccessTokenDomain::Delete(
        Request::FDeleteMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMessageAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MessageName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MessageName.IsSet() ? *MessageName : "null") + ":" +
            ChildType;
    }

    FString FMessageAccessTokenDomain::CreateCacheKey(
        TOptional<FString> MessageName
    )
    {
        return FString("") +
            (MessageName.IsSet() ? *MessageName : "null");
    }

    FMessageAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FMessageAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FMessageAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FMessage>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inbox::Model::FMessage> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inbox::Model::FMessage>(
            Self->ParentKey,
            Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                Self->MessageName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inbox::Request::FGetMessageRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    Self->MessageName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "message")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inbox::Model::FMessage>(
                Self->ParentKey,
                Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    Self->MessageName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FModelTask>> FMessageAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMessageAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMessageAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Inbox::Model::FMessagePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                MessageName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inbox::Model::FMessage>(obj));
            }
        );
    }

    void FMessageAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                MessageName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

