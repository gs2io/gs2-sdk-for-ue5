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

#include "SerialKey/Domain/Model/CampaignModelMaster.h"
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
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FCampaignModelMasterDomain::FCampaignModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CampaignModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        CampaignModelName(CampaignModelName),
        ParentKey(Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CampaignModelMaster"
        ))
    {
    }

    FCampaignModelMasterDomain::FCampaignModelMasterDomain(
        const FCampaignModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        CampaignModelName(From.CampaignModelName),
        ParentKey(From.ParentKey)
    {

    }

    FCampaignModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCampaignModelMasterDomain>& Self,
        const Request::FGetCampaignModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCampaignModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName);
        const auto Future = Self->Client->GetCampaignModelMaster(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CampaignModelMaster"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SerialKey::Model::FCampaignModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCampaignModelMasterDomain::FGetTask>> FCampaignModelMasterDomain::Get(
        Request::FGetCampaignModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCampaignModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCampaignModelMasterDomain>& Self,
        const Request::FUpdateCampaignModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCampaignModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName);
        const auto Future = Self->Client->UpdateCampaignModelMaster(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CampaignModelMaster"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::SerialKey::Model::FCampaignModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCampaignModelMasterDomain::FUpdateTask>> FCampaignModelMasterDomain::Update(
        Request::FUpdateCampaignModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCampaignModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FCampaignModelMasterDomain>& Self,
        const Request::FDeleteCampaignModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCampaignModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName);
        const auto Future = Self->Client->DeleteCampaignModelMaster(
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
                const auto ParentKey = Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CampaignModelMaster"
                );
                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::SerialKey::Model::FCampaignModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCampaignModelMasterDomain::FDeleteTask>> FCampaignModelMasterDomain::Delete(
        Request::FDeleteCampaignModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FCampaignModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> CampaignModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (CampaignModelName.IsSet() ? *CampaignModelName : "null") + ":" +
            ChildType;
    }

    FString FCampaignModelMasterDomain::CreateCacheKey(
        TOptional<FString> CampaignModelName
    )
    {
        return FString("") +
            (CampaignModelName.IsSet() ? *CampaignModelName : "null");
    }

    FCampaignModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCampaignModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FCampaignModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SerialKey::Model::FCampaignModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::SerialKey::Model::FCampaignModelMaster>(
            Self->ParentKey,
            Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                Self->CampaignModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SerialKey::Request::FGetCampaignModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                    Self->CampaignModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::SerialKey::Model::FCampaignModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "campaignModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::SerialKey::Model::FCampaignModelMaster>(
                Self->ParentKey,
                Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                    Self->CampaignModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCampaignModelMasterDomain::FModelTask>> FCampaignModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCampaignModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCampaignModelMasterDomain::Subscribe(
        TFunction<void(Gs2::SerialKey::Model::FCampaignModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SerialKey::Model::FCampaignModelMaster::TypeName,
            ParentKey,
            Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                CampaignModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SerialKey::Model::FCampaignModelMaster>(obj));
            }
        );
    }

    void FCampaignModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SerialKey::Model::FCampaignModelMaster::TypeName,
            ParentKey,
            Gs2::SerialKey::Domain::Model::FCampaignModelMasterDomain::CreateCacheKey(
                CampaignModelName
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

