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

#include "Idle/Domain/Model/CategoryModelMaster.h"
#include "Idle/Domain/Model/Namespace.h"
#include "Idle/Domain/Model/CategoryModelMaster.h"
#include "Idle/Domain/Model/CategoryModel.h"
#include "Idle/Domain/Model/User.h"
#include "Idle/Domain/Model/UserAccessToken.h"
#include "Idle/Domain/Model/Status.h"
#include "Idle/Domain/Model/StatusAccessToken.h"
#include "Idle/Domain/Model/CurrentCategoryMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Idle::Domain::Model
{

    FCategoryModelMasterDomain::FCategoryModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Idle::Domain::FGs2IdleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CategoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Idle::FGs2IdleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        CategoryName(CategoryName),
        ParentKey(Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CategoryModelMaster"
        ))
    {
    }

    FCategoryModelMasterDomain::FCategoryModelMasterDomain(
        const FCategoryModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        CategoryName(From.CategoryName),
        ParentKey(From.ParentKey)
    {

    }

    FCategoryModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCategoryModelMasterDomain>& Self,
        const Request::FGetCategoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FCategoryModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->GetCategoryModelMaster(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CategoryModelMaster"
                );
                const auto Key = Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FCategoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FGetTask>> FCategoryModelMasterDomain::Get(
        Request::FGetCategoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCategoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCategoryModelMasterDomain>& Self,
        const Request::FUpdateCategoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCategoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->UpdateCategoryModelMaster(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CategoryModelMaster"
                );
                const auto Key = Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FCategoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FUpdateTask>> FCategoryModelMasterDomain::Update(
        Request::FUpdateCategoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCategoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FCategoryModelMasterDomain>& Self,
        const Request::FDeleteCategoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FCategoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->DeleteCategoryModelMaster(
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
                const auto ParentKey = Gs2::Idle::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CategoryModelMaster"
                );
                const auto Key = Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Idle::Model::FCategoryModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FDeleteTask>> FCategoryModelMasterDomain::Delete(
        Request::FDeleteCategoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FCategoryModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> CategoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            ChildType;
    }

    FString FCategoryModelMasterDomain::CreateCacheKey(
        TOptional<FString> CategoryName
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null");
    }

    FCategoryModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCategoryModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FCategoryModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FCategoryModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Idle::Model::FCategoryModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Idle::Model::FCategoryModelMaster>(
            Self->ParentKey,
            Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                Self->CategoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Idle::Request::FGetCategoryModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    Self->CategoryName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Idle::Model::FCategoryModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "categoryModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Idle::Model::FCategoryModelMaster>(
                Self->ParentKey,
                Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    Self->CategoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FModelTask>> FCategoryModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCategoryModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCategoryModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Idle::Model::FCategoryModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Idle::Model::FCategoryModelMaster::TypeName,
            ParentKey,
            Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                CategoryName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Idle::Model::FCategoryModelMaster>(obj));
            }
        );
    }

    void FCategoryModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Idle::Model::FCategoryModelMaster::TypeName,
            ParentKey,
            Gs2::Idle::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                CategoryName
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

