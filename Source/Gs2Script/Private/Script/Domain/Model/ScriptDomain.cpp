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

#include "Script/Domain/Model/Script.h"
#include "Script/Domain/Model/Namespace.h"
#include "Script/Domain/Model/Script.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Script::Domain::Model
{

    FScriptDomain::FScriptDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Script::Domain::FGs2ScriptDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ScriptName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Script::FGs2ScriptRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ScriptName(ScriptName),
        ParentKey(Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Script"
        ))
    {
    }

    FScriptDomain::FScriptDomain(
        const FScriptDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ScriptName(From.ScriptName),
        ParentKey(From.ParentKey)
    {

    }

    FScriptDomain::FGetTask::FGetTask(
        const TSharedPtr<FScriptDomain>& Self,
        const Request::FGetScriptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FScriptDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FScriptDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Model::FScript>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithScriptName(Self->ScriptName);
        const auto Future = Self->Client->GetScript(
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
                const auto ParentKey = Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Script"
                );
                const auto Key = Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Script::Model::FScript::TypeName,
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

    TSharedPtr<FAsyncTask<FScriptDomain::FGetTask>> FScriptDomain::Get(
        Request::FGetScriptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FScriptDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FScriptDomain>& Self,
        const Request::FUpdateScriptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FScriptDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FScriptDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithScriptName(Self->ScriptName);
        const auto Future = Self->Client->UpdateScript(
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
                const auto ParentKey = Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Script"
                );
                const auto Key = Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Script::Model::FScript::TypeName,
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

    TSharedPtr<FAsyncTask<FScriptDomain::FUpdateTask>> FScriptDomain::Update(
        Request::FUpdateScriptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FScriptDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FScriptDomain>& Self,
        const Request::FUpdateScriptFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FScriptDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FScriptDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithScriptName(Self->ScriptName);
        const auto Future = Self->Client->UpdateScriptFromGitHub(
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
                const auto ParentKey = Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Script"
                );
                const auto Key = Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Script::Model::FScript::TypeName,
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

    TSharedPtr<FAsyncTask<FScriptDomain::FUpdateFromGitHubTask>> FScriptDomain::UpdateFromGitHub(
        Request::FUpdateScriptFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FScriptDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FScriptDomain>& Self,
        const Request::FDeleteScriptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FScriptDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FScriptDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithScriptName(Self->ScriptName);
        const auto Future = Self->Client->DeleteScript(
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
                const auto ParentKey = Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Script"
                );
                const auto Key = Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Script::Model::FScript::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FScriptDomain::FDeleteTask>> FScriptDomain::Delete(
        Request::FDeleteScriptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FScriptDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ScriptName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ScriptName.IsSet() ? *ScriptName : "null") + ":" +
            ChildType;
    }

    FString FScriptDomain::CreateCacheKey(
        TOptional<FString> ScriptName
    )
    {
        return FString("") +
            (ScriptName.IsSet() ? *ScriptName : "null");
    }

    FScriptDomain::FModelTask::FModelTask(
        const TSharedPtr<FScriptDomain> Self
    ): Self(Self)
    {

    }

    FScriptDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FScriptDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Model::FScript>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Script::Model::FScript> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Script::Model::FScript>(
            Self->ParentKey,
            Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                Self->ScriptName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Script::Request::FGetScriptRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                    Self->ScriptName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Script::Model::FScript::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "script")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Script::Model::FScript>(
                Self->ParentKey,
                Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                    Self->ScriptName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FScriptDomain::FModelTask>> FScriptDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FScriptDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FScriptDomain::Subscribe(
        TFunction<void(Gs2::Script::Model::FScriptPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Script::Model::FScript::TypeName,
            ParentKey,
            Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                ScriptName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Script::Model::FScript>(obj));
            }
        );
    }

    void FScriptDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Script::Model::FScript::TypeName,
            ParentKey,
            Gs2::Script::Domain::Model::FScriptDomain::CreateCacheKey(
                ScriptName
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

