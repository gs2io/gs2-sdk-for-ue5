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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Deploy/Domain/Gs2Deploy.h"
#include "Deploy/Domain/Iterator/DescribeEventsIterator.h"
#include "Deploy/Domain/Iterator/DescribeStacksIterator.h"
#include "Deploy/Domain/Iterator/DescribeResourcesIterator.h"
#include "Deploy/Domain/Iterator/DescribeEventsIterator.h"
#include "Deploy/Domain/Iterator/DescribeOutputsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Deploy::Domain
{
    class FGs2DeployDomain;
    typedef TSharedPtr<FGs2DeployDomain> FGs2DeployDomainPtr;
}

namespace Gs2::Deploy::Domain::Model
{
    class FStackDomain;
    class FResourceDomain;
    class FEventDomain;
    class FOutputDomain;

    class GS2DEPLOY_API FStackDomain:
        public TSharedFromThis<FStackDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Deploy::Domain::FGs2DeployDomainPtr Service;
        const Gs2::Deploy::FGs2DeployRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> StackName;
    private:

        FString ParentKey;

    public:

        FStackDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Deploy::Domain::FGs2DeployDomainPtr& Service,
            const TOptional<FString> StackName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStackDomain(
            const FStackDomain& From
        );

        class GS2DEPLOY_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FGetStackStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FGetStackStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetStackStatusRequestPtr Request
        );

        class GS2DEPLOY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Model::FStack>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FGetStackRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FGetStackRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FStack>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStackRequestPtr Request
        );

        class GS2DEPLOY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FUpdateStackRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FUpdateStackRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateStackRequestPtr Request
        );

        class GS2DEPLOY_API FChangeSetTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Deploy::Model::FChangeSet>>>,
            public TSharedFromThis<FChangeSetTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FChangeSetRequestPtr Request;
        public:
            explicit FChangeSetTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FChangeSetRequestPtr Request
            );

            FChangeSetTask(
                const FChangeSetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Deploy::Model::FChangeSet>>>> Result
            ) override;
        };
        friend FChangeSetTask;

        TSharedPtr<FAsyncTask<FChangeSetTask>> ChangeSet(
            Request::FChangeSetRequestPtr Request
        );

        class GS2DEPLOY_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FUpdateStackFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FUpdateStackFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateStackFromGitHubRequestPtr Request
        );

        class GS2DEPLOY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FDeleteStackRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FDeleteStackRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteStackRequestPtr Request
        );

        class GS2DEPLOY_API FForceDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FForceDeleteTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FForceDeleteStackRequestPtr Request;
        public:
            explicit FForceDeleteTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FForceDeleteStackRequestPtr Request
            );

            FForceDeleteTask(
                const FForceDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FForceDeleteTask;

        TSharedPtr<FAsyncTask<FForceDeleteTask>> ForceDelete(
            Request::FForceDeleteStackRequestPtr Request
        );

        class GS2DEPLOY_API FDeleteResourcesTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FDeleteResourcesTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FDeleteStackResourcesRequestPtr Request;
        public:
            explicit FDeleteResourcesTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FDeleteStackResourcesRequestPtr Request
            );

            FDeleteResourcesTask(
                const FDeleteResourcesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FDeleteResourcesTask;

        TSharedPtr<FAsyncTask<FDeleteResourcesTask>> DeleteResources(
            Request::FDeleteStackResourcesRequestPtr Request
        );

        class GS2DEPLOY_API FDeleteEntityTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FDeleteEntityTask>
        {
            const TSharedPtr<FStackDomain> Self;
            const Request::FDeleteStackEntityRequestPtr Request;
        public:
            explicit FDeleteEntityTask(
                const TSharedPtr<FStackDomain>& Self,
                const Request::FDeleteStackEntityRequestPtr Request
            );

            FDeleteEntityTask(
                const FDeleteEntityTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FDeleteEntityTask;

        TSharedPtr<FAsyncTask<FDeleteEntityTask>> DeleteEntity(
            Request::FDeleteStackEntityRequestPtr Request
        );

        Gs2::Deploy::Domain::Iterator::FDescribeResourcesIteratorPtr Resources(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeResources(
            TFunction<void()> Callback
        );

        void UnsubscribeResources(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Deploy::Domain::Model::FResourceDomain> Resource(
            const FString ResourceName
        );

        Gs2::Deploy::Domain::Iterator::FDescribeEventsIteratorPtr Events(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEvents(
            TFunction<void()> Callback
        );

        void UnsubscribeEvents(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Deploy::Domain::Model::FEventDomain> Event(
            const FString EventName
        );

        Gs2::Deploy::Domain::Iterator::FDescribeOutputsIteratorPtr Outputs(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeOutputs(
            TFunction<void()> Callback
        );

        void UnsubscribeOutputs(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Deploy::Domain::Model::FOutputDomain> Output(
            const FString OutputName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> StackName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> StackName
        );

        class GS2DEPLOY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Model::FStack>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStackDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStackDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FStack>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Deploy::Model::FStackPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStackDomain> FStackDomainPtr;
}
