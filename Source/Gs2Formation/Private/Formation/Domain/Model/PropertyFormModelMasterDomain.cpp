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

#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FPropertyFormModelMasterDomain::FPropertyFormModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PropertyFormModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        PropertyFormModelName(PropertyFormModelName),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "PropertyFormModelMaster"
        ))
    {
    }

    FPropertyFormModelMasterDomain::FPropertyFormModelMasterDomain(
        const FPropertyFormModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        PropertyFormModelName(From.PropertyFormModelName),
        ParentKey(From.ParentKey)
    {

    }

    FPropertyFormModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FPropertyFormModelMasterDomain>& Self,
        const Request::FGetPropertyFormModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyFormModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPropertyFormModelName(Self->PropertyFormModelName);
        const auto Future = Self->Client->GetPropertyFormModelMaster(
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

    TSharedPtr<FAsyncTask<FPropertyFormModelMasterDomain::FGetTask>> FPropertyFormModelMasterDomain::Get(
        Request::FGetPropertyFormModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPropertyFormModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FPropertyFormModelMasterDomain>& Self,
        const Request::FUpdatePropertyFormModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPropertyFormModelName(Self->PropertyFormModelName);
        const auto Future = Self->Client->UpdatePropertyFormModelMaster(
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

    TSharedPtr<FAsyncTask<FPropertyFormModelMasterDomain::FUpdateTask>> FPropertyFormModelMasterDomain::Update(
        Request::FUpdatePropertyFormModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FPropertyFormModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPropertyFormModelMasterDomain>& Self,
        const Request::FDeletePropertyFormModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPropertyFormModelName(Self->PropertyFormModelName);
        const auto Future = Self->Client->DeletePropertyFormModelMaster(
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

    TSharedPtr<FAsyncTask<FPropertyFormModelMasterDomain::FDeleteTask>> FPropertyFormModelMasterDomain::Delete(
        Request::FDeletePropertyFormModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPropertyFormModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> PropertyFormModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (PropertyFormModelName.IsSet() ? *PropertyFormModelName : "null") + ":" +
            ChildType;
    }

    FString FPropertyFormModelMasterDomain::CreateCacheKey(
        TOptional<FString> PropertyFormModelName
    )
    {
        return FString("") +
            (PropertyFormModelName.IsSet() ? *PropertyFormModelName : "null");
    }

    FPropertyFormModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FPropertyFormModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FPropertyFormModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyFormModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FPropertyFormModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FPropertyFormModelMaster>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain::CreateCacheKey(
                Self->PropertyFormModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetPropertyFormModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain::CreateCacheKey(
                    Self->PropertyFormModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FPropertyFormModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "propertyFormModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FPropertyFormModelMaster>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain::CreateCacheKey(
                    Self->PropertyFormModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormModelMasterDomain::FModelTask>> FPropertyFormModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPropertyFormModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FPropertyFormModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FPropertyFormModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FPropertyFormModelMaster::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain::CreateCacheKey(
                PropertyFormModelName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FPropertyFormModelMaster>(obj));
            }
        );
    }

    void FPropertyFormModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FPropertyFormModelMaster::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FPropertyFormModelMasterDomain::CreateCacheKey(
                PropertyFormModelName
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

