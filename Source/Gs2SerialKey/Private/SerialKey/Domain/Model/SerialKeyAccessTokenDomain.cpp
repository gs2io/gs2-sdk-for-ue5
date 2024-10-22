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

#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/Namespace.h"
#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/UserAccessToken.h"
#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/CampaignModelMaster.h"
#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FSerialKeyAccessTokenDomain::FSerialKeyAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> SerialKeyCode
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        SerialKeyCode(SerialKeyCode),
        ParentKey(Gs2::SerialKey::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "SerialKey"
        ))
    {
    }

    FSerialKeyAccessTokenDomain::FSerialKeyAccessTokenDomain(
        const FSerialKeyAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        SerialKeyCode(From.SerialKeyCode),
        ParentKey(From.ParentKey)
    {

    }

    FSerialKeyAccessTokenDomain::FUseTask::FUseTask(
        const TSharedPtr<FSerialKeyAccessTokenDomain>& Self,
        const Request::FUseRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSerialKeyAccessTokenDomain::FUseTask::FUseTask(
        const FUseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyAccessTokenDomain::FUseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->Use(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "SerialKey"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCode()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SerialKey::Model::FSerialKey::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetCampaignModel() != nullptr)
            {
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CampaignModel"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheKey(
                    ResultModel->GetCampaignModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SerialKey::Model::FCampaignModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetCampaignModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSerialKeyAccessTokenDomain::FUseTask>> FSerialKeyAccessTokenDomain::Use(
        Request::FUseRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUseTask>>(this->AsShared(), Request);
    }

    FString FSerialKeyAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> SerialKeyCode,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (SerialKeyCode.IsSet() ? *SerialKeyCode : "null") + ":" +
            ChildType;
    }

    FString FSerialKeyAccessTokenDomain::CreateCacheKey(
        TOptional<FString> SerialKeyCode
    )
    {
        return FString("") +
            (SerialKeyCode.IsSet() ? *SerialKeyCode : "null");
    }

    FSerialKeyAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSerialKeyAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSerialKeyAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SerialKey::Model::FSerialKey> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::SerialKey::Model::FSerialKey>(
            Self->ParentKey,
            Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                Self->SerialKeyCode
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSerialKeyAccessTokenDomain::FModelTask>> FSerialKeyAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSerialKeyAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSerialKeyAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::SerialKey::Model::FSerialKeyPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            ParentKey,
            Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                SerialKeyCode
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SerialKey::Model::FSerialKey>(obj));
            }
        );
    }

    void FSerialKeyAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            ParentKey,
            Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                SerialKeyCode
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

