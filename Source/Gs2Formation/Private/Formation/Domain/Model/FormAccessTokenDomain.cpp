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

#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/Form.h"
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

    FFormAccessTokenDomain::FFormAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> MoldModelName,
        const TOptional<int32> Index
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        MoldModelName(MoldModelName),
        Index(Index),
        ParentKey(Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            MoldModelName,
            "Form"
        ))
    {
    }

    FFormAccessTokenDomain::FFormAccessTokenDomain(
        const FFormAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        MoldModelName(From.MoldModelName),
        Index(From.Index),
        ParentKey(From.ParentKey)
    {

    }

    FFormAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FFormAccessTokenDomain> Self,
        const Request::FGetFormRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->GetForm(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
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
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FFormModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormAccessTokenDomain::FGetTask>> FFormAccessTokenDomain::Get(
        Request::FGetFormRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFormAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FFormAccessTokenDomain> Self,
        const Request::FGetFormWithSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormAccessTokenDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->GetFormWithSignature(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
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
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FFormModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Body = *ResultModel->GetBody();
        Domain->Signature = *ResultModel->GetSignature();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormAccessTokenDomain::FGetWithSignatureTask>> FFormAccessTokenDomain::GetWithSignature(
        Request::FGetFormWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FFormAccessTokenDomain::FSetWithSignatureTask::FSetWithSignatureTask(
        const TSharedPtr<FFormAccessTokenDomain> Self,
        const Request::FSetFormWithSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormAccessTokenDomain::FSetWithSignatureTask::FSetWithSignatureTask(
        const FSetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormAccessTokenDomain::FSetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->SetFormWithSignature(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
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
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FFormModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormAccessTokenDomain::FSetWithSignatureTask>> FFormAccessTokenDomain::SetWithSignature(
        Request::FSetFormWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetWithSignatureTask>>(this->AsShared(), Request);
    }

    FFormAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFormAccessTokenDomain> Self,
        const Request::FDeleteFormRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->DeleteForm(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Cache->Delete(Gs2::Formation::Model::FForm::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Cache->Delete(Gs2::Formation::Model::FMold::TypeName, ParentKey, Key);
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
                Self->Cache->Delete(Gs2::Formation::Model::FMoldModel::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Delete(Gs2::Formation::Model::FFormModel::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormAccessTokenDomain::FDeleteTask>> FFormAccessTokenDomain::Delete(
        Request::FDeleteFormRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFormAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MoldModelName,
        TOptional<FString> Index,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MoldModelName.IsSet() ? *MoldModelName : "null") + ":" +
            (Index.IsSet() ? *Index : "null") + ":" +
            ChildType;
    }

    FString FFormAccessTokenDomain::CreateCacheKey(
        TOptional<FString> Index
    )
    {
        return FString("") +
            (Index.IsSet() ? *Index : "null");
    }

    FFormAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FFormAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FFormAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFormAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FForm> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Formation::Model::FForm>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetFormRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "form")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Formation::Model::FForm>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormAccessTokenDomain::FModelTask>> FFormAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFormAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FFormAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FFormPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Formation::Model::FForm::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                Index.IsSet() ? FString::FromInt(*Index) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FForm>(obj));
            }
        );
    }

    void FFormAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                Index.IsSet() ? FString::FromInt(*Index) : TOptional<FString>()
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

