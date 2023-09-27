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

#include "Formation/Domain/Model/PropertyFormModel.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FPropertyFormModelDomain::FPropertyFormModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PropertyFormModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        PropertyFormModelName(PropertyFormModelName),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "PropertyFormModel"
        ))
    {
    }

    FPropertyFormModelDomain::FPropertyFormModelDomain(
        const FPropertyFormModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        PropertyFormModelName(From.PropertyFormModelName),
        ParentKey(From.ParentKey)
    {

    }

    FPropertyFormModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FPropertyFormModelDomain> Self,
        const Request::FGetPropertyFormModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyFormModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPropertyFormModelName(Self->PropertyFormModelName);
        const auto Future = Self->Client->GetPropertyFormModel(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "PropertyFormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FPropertyFormModel::TypeName,
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

    TSharedPtr<FAsyncTask<FPropertyFormModelDomain::FGetTask>> FPropertyFormModelDomain::Get(
        Request::FGetPropertyFormModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FPropertyFormModelDomain::CreateCacheParentKey(
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

    FString FPropertyFormModelDomain::CreateCacheKey(
        TOptional<FString> PropertyFormModelName
    )
    {
        return FString("") +
            (PropertyFormModelName.IsSet() ? *PropertyFormModelName : "null");
    }

    FPropertyFormModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FPropertyFormModelDomain> Self
    ): Self(Self)
    {

    }

    FPropertyFormModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyFormModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FPropertyFormModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Formation::Model::FPropertyFormModel>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FPropertyFormModelDomain::CreateCacheKey(
                Self->PropertyFormModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetPropertyFormModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormModelDomain::CreateCacheKey(
                    Self->PropertyFormModelName
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FPropertyFormModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "propertyFormModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Formation::Model::FPropertyFormModel>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FPropertyFormModelDomain::CreateCacheKey(
                    Self->PropertyFormModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormModelDomain::FModelTask>> FPropertyFormModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPropertyFormModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FPropertyFormModelDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FPropertyFormModelPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Formation::Model::FPropertyFormModel::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FPropertyFormModelDomain::CreateCacheKey(
                PropertyFormModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FPropertyFormModel>(obj));
            }
        );
    }

    void FPropertyFormModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Formation::Model::FPropertyFormModel::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FPropertyFormModelDomain::CreateCacheKey(
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

