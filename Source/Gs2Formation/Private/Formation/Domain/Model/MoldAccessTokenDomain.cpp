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

#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Mold.h"
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
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FMoldAccessTokenDomain::FMoldAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> MoldModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        MoldModelName(MoldModelName),
        ParentKey(Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Mold"
        ))
    {
    }

    FMoldAccessTokenDomain::FMoldAccessTokenDomain(
        const FMoldAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        MoldModelName(From.MoldModelName),
        ParentKey(From.ParentKey)
    {

    }

    FMoldAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FMoldAccessTokenDomain>& Self,
        const Request::FGetMoldRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->GetMold(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldAccessTokenDomain::FGetTask>> FMoldAccessTokenDomain::Get(
        Request::FGetMoldRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMoldAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMoldAccessTokenDomain>& Self,
        const Request::FDeleteMoldRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->DeleteMold(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Formation::Model::FMold::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldAccessTokenDomain::FDeleteTask>> FMoldAccessTokenDomain::Delete(
        Request::FDeleteMoldRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Formation::Domain::Iterator::FDescribeFormsIteratorPtr FMoldAccessTokenDomain::Forms(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeFormsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            MoldModelName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FMoldAccessTokenDomain::SubscribeForms(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                MoldModelName,
                "Form"
            ),
            Callback
        );
    }

    void FMoldAccessTokenDomain::UnsubscribeForms(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                MoldModelName,
                "Form"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain> FMoldAccessTokenDomain::Form(
        const int32 Index
    )
    {
        return MakeShared<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            MoldModelName,
            Index
        );
    }

    FString FMoldAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MoldModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MoldModelName.IsSet() ? *MoldModelName : "null") + ":" +
            ChildType;
    }

    FString FMoldAccessTokenDomain::CreateCacheKey(
        TOptional<FString> MoldModelName
    )
    {
        return FString("") +
            (MoldModelName.IsSet() ? *MoldModelName : "null");
    }

    FMoldAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FMoldAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FMoldAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FMold> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FMold>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                Self->MoldModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetMoldRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    Self->MoldModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "mold")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FMold>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    Self->MoldModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldAccessTokenDomain::FModelTask>> FMoldAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMoldAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMoldAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FMoldPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FMold::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                MoldModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FMold>(obj));
            }
        );
    }

    void FMoldAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FMold::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                MoldModelName
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

