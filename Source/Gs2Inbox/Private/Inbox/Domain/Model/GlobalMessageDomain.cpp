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

#include "Inbox/Domain/Model/GlobalMessage.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FGlobalMessageDomain::FGlobalMessageDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GlobalMessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Session)),
        NamespaceName(NamespaceName),
        GlobalMessageName(GlobalMessageName),
        ParentKey(Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "GlobalMessage"
        ))
    {
    }

    FGlobalMessageDomain::FGlobalMessageDomain(
        const FGlobalMessageDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GlobalMessageName(From.GlobalMessageName),
        ParentKey(From.ParentKey)
    {

    }

    FGlobalMessageDomain::FGetTask::FGetTask(
        const TSharedPtr<FGlobalMessageDomain> Self,
        const Request::FGetGlobalMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalMessageDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessage>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
        const auto Future = Self->Client->GetGlobalMessage(
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
                const auto ParentKey = Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "GlobalMessage"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FGlobalMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inbox::Model::FGlobalMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalMessageDomain::FGetTask>> FGlobalMessageDomain::Get(
        Request::FGetGlobalMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FGlobalMessageDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GlobalMessageName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GlobalMessageName.IsSet() ? *GlobalMessageName : "null") + ":" +
            ChildType;
    }

    FString FGlobalMessageDomain::CreateCacheKey(
        TOptional<FString> GlobalMessageName
    )
    {
        return FString("") +
            (GlobalMessageName.IsSet() ? *GlobalMessageName : "null");
    }

    FGlobalMessageDomain::FModelTask::FModelTask(
        const TSharedPtr<FGlobalMessageDomain> Self
    ): Self(Self)
    {

    }

    FGlobalMessageDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessage>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inbox::Model::FGlobalMessage> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Inbox::Model::FGlobalMessage>(
            Self->ParentKey,
            Gs2::Inbox::Domain::Model::FGlobalMessageDomain::CreateCacheKey(
                Self->GlobalMessageName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inbox::Request::FGetGlobalMessageRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inbox::Domain::Model::FGlobalMessageDomain::CreateCacheKey(
                    Self->GlobalMessageName
                );
                Self->Cache->Put(
                    Gs2::Inbox::Model::FGlobalMessage::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "globalMessage")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Inbox::Model::FGlobalMessage>(
                Self->ParentKey,
                Gs2::Inbox::Domain::Model::FGlobalMessageDomain::CreateCacheKey(
                    Self->GlobalMessageName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalMessageDomain::FModelTask>> FGlobalMessageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGlobalMessageDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FGlobalMessageDomain::Subscribe(
        TFunction<void(Gs2::Inbox::Model::FGlobalMessagePtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Inbox::Model::FGlobalMessage::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FGlobalMessageDomain::CreateCacheKey(
                GlobalMessageName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inbox::Model::FGlobalMessage>(obj));
            }
        );
    }

    void FGlobalMessageDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Inbox::Model::FGlobalMessage::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FGlobalMessageDomain::CreateCacheKey(
                GlobalMessageName
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

