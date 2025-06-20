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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FMessageDomain::FMessageDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> MessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        MessageName(MessageName),
        ParentKey(Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Message"
        ))
    {
    }

    FMessageDomain::FMessageDomain(
        const FMessageDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        MessageName(From.MessageName),
        ParentKey(From.ParentKey)
    {

    }

    FMessageDomain::FGetTask::FGetTask(
        const TSharedPtr<FMessageDomain>& Self,
        const Request::FGetMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FMessage>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->GetMessageByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FGetTask>> FMessageDomain::Get(
        Request::FGetMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMessageDomain::FOpenTask::FOpenTask(
        const TSharedPtr<FMessageDomain>& Self,
        const Request::FOpenMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageDomain::FOpenTask::FOpenTask(
        const FOpenTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FOpenTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->OpenMessageByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FOpenTask>> FMessageDomain::Open(
        Request::FOpenMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FOpenTask>>(this->AsShared(), Request);
    }

    FMessageDomain::FCloseTask::FCloseTask(
        const TSharedPtr<FMessageDomain>& Self,
        const Request::FCloseMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageDomain::FCloseTask::FCloseTask(
        const FCloseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FCloseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->CloseMessageByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FCloseTask>> FMessageDomain::Close(
        Request::FCloseMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCloseTask>>(this->AsShared(), Request);
    }

    FMessageDomain::FReadTask::FReadTask(
        const TSharedPtr<FMessageDomain>& Self,
        const Request::FReadMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageDomain::FReadTask::FReadTask(
        const FReadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FReadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->ReadMessageByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            *ResultModel->GetTransactionId(),
            *ResultModel->GetStampSheet(),
            *ResultModel->GetStampSheetEncryptionKeyId(),
            *ResultModel->GetAtomicCommit(),
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FReadTask>> FMessageDomain::Read(
        Request::FReadMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReadTask>>(this->AsShared(), Request);
    }

    FMessageDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMessageDomain>& Self,
        const Request::FDeleteMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->DeleteMessageByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FDeleteTask>> FMessageDomain::Delete(
        Request::FDeleteMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMessageDomain::CreateCacheParentKey(
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

    FString FMessageDomain::CreateCacheKey(
        TOptional<FString> MessageName
    )
    {
        return FString("") +
            (MessageName.IsSet() ? *MessageName : "null");
    }

    FMessageDomain::FModelTask::FModelTask(
        const TSharedPtr<FMessageDomain> Self
    ): Self(Self)
    {

    }

    FMessageDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FModelTask::Action(
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
                MakeShared<Gs2::Inbox::Request::FGetMessageByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FMessageDomain::FModelTask>> FMessageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMessageDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMessageDomain::Subscribe(
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

    void FMessageDomain::Unsubscribe(
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

