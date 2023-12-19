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

namespace Gs2::SerialKey::Domain::Model
{

    FSerialKeyDomain::FSerialKeyDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> SerialKeyCode
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        SerialKeyCode(SerialKeyCode),
        ParentKey(Gs2::SerialKey::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "SerialKey"
        ))
    {
    }

    FSerialKeyDomain::FSerialKeyDomain(
        const FSerialKeyDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        SerialKeyCode(From.SerialKeyCode),
        ParentKey(From.ParentKey)
    {

    }

    FSerialKeyDomain::FGetTask::FGetTask(
    const TSharedPtr<FSerialKeyDomain> Self,
    const Request::FGetSerialKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSerialKeyDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCode(Self->SerialKeyCode);
        const auto Future = Self->Client->GetSerialKey(
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
                    Self->UserId,
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSerialKeyDomain::FGetTask>> FSerialKeyDomain::Get(
        Request::FGetSerialKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSerialKeyDomain::FUseTask::FUseTask(
        const TSharedPtr<FSerialKeyDomain>& Self,
        const Request::FUseByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSerialKeyDomain::FUseTask::FUseTask(
        const FUseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyDomain::FUseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UseByUserId(
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
                    Self->UserId,
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

    TSharedPtr<FAsyncTask<FSerialKeyDomain::FUseTask>> FSerialKeyDomain::Use(
        Request::FUseByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUseTask>>(this->AsShared(), Request);
    }

    FString FSerialKeyDomain::CreateCacheParentKey(
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

    FString FSerialKeyDomain::CreateCacheKey(
        TOptional<FString> SerialKeyCode
    )
    {
        return FString("") +
            (SerialKeyCode.IsSet() ? *SerialKeyCode : "null");
    }

    FSerialKeyDomain::FModelTask::FModelTask(
        const TSharedPtr<FSerialKeyDomain> Self
    ): Self(Self)
    {

    }

    FSerialKeyDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyDomain::FModelTask::Action(
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
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SerialKey::Request::FGetSerialKeyRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                    Self->SerialKeyCode
                );
                Self->Gs2->Cache->Put(
                    Gs2::SerialKey::Model::FSerialKey::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "serialKey")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::SerialKey::Model::FSerialKey>(
                Self->ParentKey,
                Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                    Self->SerialKeyCode
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSerialKeyDomain::FModelTask>> FSerialKeyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSerialKeyDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSerialKeyDomain::Subscribe(
        TFunction<void(Gs2::SerialKey::Model::FSerialKeyPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            ParentKey,
            Gs2::SerialKey::Domain::Model::FSerialKeyDomain::CreateCacheKey(
                SerialKeyCode
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SerialKey::Model::FSerialKey>(obj));
            }
        );
    }

    void FSerialKeyDomain::Unsubscribe(
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

